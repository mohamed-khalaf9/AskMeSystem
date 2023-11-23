#include "QuestionModelView.h"
#include <iostream>



QuestionModelView::QuestionModelView() {
}
void QuestionModelView::Print_to_Question(const QuestionModel& question)const {
	std::string prefix = "";

	if (question.get_parent_question_id() != -1)
		prefix = "\tThread: ";

	std::cout << prefix << "Question Id (" << question.get_question_id() << ")";
	if (!question.get_is_anonymous_question())
		std::cout << " from user id(" << question.get_from_user_id() << ")";
	std::cout << "\t Question: " << question.get_question_text() << "\n";

	if (question.get_answer_text() != "")
		std::cout << prefix << "\tAnswer: " << question.get_answer_text() << "\n";
	std::cout << "\n";
}
void QuestionModelView::Print_from_Question(const QuestionModel& question)const {
	std::cout << "Question Id (" << question.get_question_id() << ")";
	if (!question.get_is_anonymous_question())
		std::cout << " !AQ";

	std::cout << " to user id(" << question.get_to_user_id() << ")";
	std::cout << "\t Question: " << question.get_question_text();

	if (question.get_answer_text() != "")
		std::cout << "\tAnswer: " << question.get_answer_text() << "\n";
	else
		std::cout << "\tNOT Answered YET\n";
}
void QuestionModelView::Print_feed_Question(const QuestionModel& question)const {
	if (question.get_parent_question_id() != -1)
		std::cout << "Thread Parent Question ID (" << question.get_parent_question_id() << ") ";

	std::cout << "Question Id (" << question.get_question_id() << ")";
	if (!question.get_is_anonymous_question())
		std::cout << " from user id(" << question.get_from_user_id() << ")";

	std::cout << " To user id(" << question.get_to_user_id() << ")";

	std::cout << "\t Question: " << question.get_question_text() << "\n";
	if (question.get_answer_text() != "")
		std::cout << "\tAnswer: " << question.get_answer_text() << "\n";
}
