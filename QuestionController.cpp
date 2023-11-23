#include "QuestionController.h"
#include "QuestionModel.h"
#include "QuestionModelView.h"
#include "HelperFunctions.h"
#include "UserModel.h"
#include <iostream>
#include <map>
#include <vector>


QuestionController::QuestionController() :last_id(0) {
}
void QuestionController::LoadDatabase() {
	last_id = 0;
	questionid_questionidsThead_to_map.clear();
	questionid_questionobject_map.clear();
	HelperFunctions helper;
	std::vector<std::string> lines = helper.ReadFileLines("questions.txt");
	for (auto& line : lines) {
		QuestionModel question(line);
		last_id = std::max(last_id, question.get_question_id());

		questionid_questionobject_map[question.get_question_id()] = question;

		if (question.get_parent_question_id() == -1)
			questionid_questionidsThead_to_map[question.get_question_id()].push_back(question.get_question_id());
		else
			questionid_questionidsThead_to_map[question.get_parent_question_id()].push_back(question.get_question_id());
	}

}
std::vector<int> QuestionController::GetUserToQuestions(const UserModel& user) const {
	std::vector<int> question_ids;

	for (const auto& pair : questionid_questionidsThead_to_map) {	// pair<int, vector<Question>>
		for (const auto& question_id : pair.second) {		//  vector<Question>

			// Get the question from the map. (&) means same in memory
			const QuestionModel& question = questionid_questionobject_map.find(question_id)->second;

			if (question.get_from_user_id() == user.get_user_id())
				question_ids.push_back(question.get_question_id());
		}
	}
	return question_ids;
}
std::vector<std::pair<int, int>> QuestionController::GetUserFromQuestions(const UserModel& user) const {
	std::vector<std::pair<int, int>> question_ids;

	for (const auto& pair : questionid_questionidsThead_to_map) {	// pair<int, vector<Question>>
		for (const auto& question_id : pair.second) {		//  vector<Question>
			// Get the question from the map. & means same in memory, 
			const QuestionModel& question = questionid_questionobject_map.find(question_id)->second;

			if (question.get_to_user_id() == user.get_user_id()) {
				if (question.get_parent_question_id() == -1)
					question_ids.push_back(std::make_pair(question.get_question_id(), question.get_question_id()));
				else
					question_ids.push_back(std::make_pair(question.get_parent_question_id(), question.get_question_id()));
			}
		}
	}
	return question_ids;
}

int QuestionController::ReadQuestionIdAny(const UserModel& user) {
	int question_id;
	std::cout << "Enter Question id or -1 to cancel: ";
	std::cin >> question_id;

	if (question_id == -1)
		return -1;

	if (!questionid_questionobject_map.count(question_id)) {
		std::cout << "\nERROR: No question with such ID. Try again\n\n";
		return ReadQuestionIdAny(user);
	}
	QuestionModel& question = questionid_questionobject_map[question_id];

	if (question.get_to_user_id() != user.get_user_id()) {
		std::cout << "\nERROR: Invalid question ID. Try again\n\n";
		return ReadQuestionIdAny(user);
	}
	return question_id;
}
int QuestionController::ReadQuestionIdThread(const UserModel& user) {
	int question_id;
	std::cout << "For thread question: Enter Question id or -1 for new question: ";
	std::cin >> question_id;

	if (question_id == -1)
		return -1;

	if (!questionid_questionidsThead_to_map.count(question_id)) {
		std::cout << "No thread question with such ID. Try again\n";
		return ReadQuestionIdThread(user);
	}
	return question_id;

}
void QuestionController::AnswerQuestion(const UserModel& user) {
	int question_id = ReadQuestionIdAny(user);

	if (question_id == -1)
		return;

	QuestionModel& question = questionid_questionobject_map.find(question_id)->second;

	QuestionModelView question_view;
	question_view.Print_to_Question(question);


	if (question.get_answer_text() != "")
		std::cout << "\nWarning: Already answered. Answer will be updated\n";

	std::cout << "Enter answer: ";	// if user entered comma, system fails :)

	std::string line;
	getline(std::cin, line);
	getline(std::cin, line);
	question.set_answer_text(line);
}

void QuestionController::DeleteQuestion(const UserModel& user) {
	int question_id = ReadQuestionIdAny(user);

	if (question_id == -1)
		return;

	std::vector<int> ids_to_remove;	// to remove from questionid_questionobject_map

	// Let's see if thread or not. If thread, remove all of it
	if (questionid_questionidsThead_to_map.count(question_id)) { // thread
		ids_to_remove = questionid_questionidsThead_to_map[question_id];
		questionid_questionidsThead_to_map.erase(question_id);
	}
	else {
		ids_to_remove.push_back(question_id);

		// let's find in which thread to remove. Consistency is important when have multi-view
		for (auto& pair : questionid_questionidsThead_to_map) {
			std::vector<int>& vec = pair.second;
			for (int pos = 0; pos < (int)vec.size(); ++pos) {
				if (question_id == vec[pos]) {
					vec.erase(vec.begin() + pos);
					break;
				}
			}
		}
	}
	for (const auto& id : ids_to_remove)
		questionid_questionobject_map.erase(id);
}
void QuestionController::AskQuestion(const UserModel& user, std::pair<int, int> to_user_pair) {
	QuestionModel question;

	if (!to_user_pair.second) {
		std::cout << "Note: Anonymous questions are not allowed for this user\n";
		question.set_is_anonymous_question(0);
	}
	else {
		std::cout << "Is anonymous questions?: (0 or 1): ";
		int st;
		std::cin >> st;
		question.set_is_anonymous_question(st);
	}

	question.set_parent_question_id(ReadQuestionIdThread(user));

	std::cout << "Enter question text: ";	// if user entered comma, system fails :)
	std::string line;
	getline(std::cin, line);
	getline(std::cin, line);
	question.set_question_text(line);

	question.set_from_user_id(user.get_user_id());
	question.set_to_user_id(to_user_pair.first);

	// What happens in 2 parallel sessions who asked question?
	// They are given same id. This is wrong handling :)
	question.set_question_id(++last_id);

	questionid_questionobject_map[question.get_question_id()] = question;

	if (question.get_parent_question_id() == -1)
		questionid_questionidsThead_to_map[question.get_question_id()].push_back(question.get_question_id());
	else
		questionid_questionidsThead_to_map[question.get_parent_question_id()].push_back(question.get_question_id());
}
void QuestionController::PrintUserToQuestions(const UserModel& user)
{
	std::cout << "\n";

	if (user.get_questionid_questionidsThead_to_map().size() == 0)
		std::cout << "No Questions";

	for (const auto& pair : user.get_questionid_questionidsThead_to_map()) {		// pair<int, vector<Question>>
		for (const auto& question_id : pair.second) {		//  vector<Question>

			// Get the question from the map. & means same in memory
			// Accessing questionid_questionobject_map[] change the map by adding if not exist. You can't use in const function
			// Here we just find, which return iterator (second is like a pointer to object)
			const QuestionModel& question = questionid_questionobject_map.find(question_id)->second;
			QuestionModelView question_view;
			question_view.Print_to_Question(question);
		}
	}
	std::cout << "\n";
}
void QuestionController::PrintUserFromQuestions(const UserModel& user)
{
	std::cout << "\n";
	if (user.get_questions_id_from_me().size() == 0)
		std::cout << "No Questions";

	for (const auto& question_id : user.get_questions_id_from_me()) {		//  vector<Question>
		const QuestionModel& question = questionid_questionobject_map.find(question_id)->second;
		QuestionModelView question_view;
		question_view.Print_from_Question(question);
	}
	std::cout << "\n";

}
void QuestionController::ListFeed() {
	for (auto& pair : questionid_questionobject_map) {
		QuestionModel& question = pair.second;

		if (question.get_answer_text() == "")
			continue;
		QuestionModelView question_view;
		question_view.Print_feed_Question(question);
	}

}
void QuestionController::UpdateDatabase() {
	std::vector<std::string> lines;

	for (auto& pair : questionid_questionobject_map)
		lines.push_back(pair.second.ToString());
	HelperFunctions helper;
	helper.WriteFileLines("questions.txt", lines, false);
}