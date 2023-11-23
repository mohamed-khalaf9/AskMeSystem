#include "AskMeSystem.h"
#include "HelperFunctions.h"
#include "UserModel.h"
#include <iostream>
#include <vector>
#include <string>




AskMeSystem::AskMeSystem() {
}
void AskMeSystem::LoadDatabase(bool fill_user_questions)
{
	user_controller.LoadDatabase();
	question_controller.LoadDatabase();

	if (fill_user_questions)
		ResetCurrentUserQuestions();

}
void AskMeSystem::ResetCurrentUserQuestions() {
	const UserModel& user = user_controller.GetCurrentUser();

	const auto& to_questions = question_controller.GetUserToQuestions(user);
	user_controller.ResetToQuestions(to_questions);

	const auto& from_questions = question_controller.GetUserFromQuestions(user);
	user_controller.ResetFromQuestions(from_questions);
}

void AskMeSystem::run()
{
	LoadDatabase(false);
	user_controller.AccessSystem();
	ResetCurrentUserQuestions();

	std::vector<std::string> menu;
	menu.push_back("Print Questions To Me");
	menu.push_back("Print Questions From Me");
	menu.push_back("Answer Question");
	menu.push_back("Delete Question");
	menu.push_back("Ask Question");
	menu.push_back("List System Users");
	menu.push_back("Feed");
	menu.push_back("Logout");

	while (true) {
		HelperFunctions helper_functions;
		int choice = helper_functions.ShowReadMenu(menu);
		LoadDatabase(true);

		if (choice == 1)
			question_controller.PrintUserToQuestions(user_controller.GetCurrentUser());
		else if (choice == 2)
			question_controller.PrintUserFromQuestions(user_controller.GetCurrentUser());
		else if (choice == 3) {
			question_controller.AnswerQuestion(user_controller.GetCurrentUser());
			question_controller.UpdateDatabase();
		}
		else if (choice == 4) {
			question_controller.DeleteQuestion(user_controller.GetCurrentUser());
			ResetCurrentUserQuestions();
			question_controller.UpdateDatabase();
		}
		else if (choice == 5) {
			std::pair<int, int> to_user_pair = user_controller.ReadUserId();
			if (to_user_pair.first != -1) {
				question_controller.AskQuestion(user_controller.GetCurrentUser(), to_user_pair);
				question_controller.UpdateDatabase();
			}
		}
		else if (choice == 6)
			user_controller.ListUsersNamesIds();
		else if (choice == 7)
			question_controller.ListFeed();
		else
			break;
	}
	run();
}
