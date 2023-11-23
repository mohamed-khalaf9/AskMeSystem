#include "UserController.h"
#include "HelperFunctions.h"
#include "UserModelView.h"
#include "UserModel.h"
#include <map>
#include <vector>
#include <iostream>





UserController::UserController() :last_id(0) {

}
void UserController::LoadDatabase() {
	last_id = 0;
	userame_userobject_map.clear();
	HelperFunctions helper;
	std::vector<std::string> lines = helper.ReadFileLines("users.txt");
	for (auto& line : lines) {
		UserModel user(line);
		userame_userobject_map[user.get_user_name()] = user;
		last_id = std::max(last_id, user.get_user_id());
	}
}
void UserController::AccessSystem()
{
	HelperFunctions helper;
	int choice = helper.ShowReadMenu({ "Login", "Sign Up" });
	if (choice == 1)
		DoLogin();
	else
		DoSignUp();
}
void UserController::DoLogin() {
	LoadDatabase();	// in case user added from other parallel run

	while (true) {
		std::string name, pass;
		std::cout << "Enter user name & password: ";
		std::cin >> name >> pass;
		current_user.set_user_name(name);
		current_user.set_password(pass);

		if (!userame_userobject_map.count(current_user.get_user_name())) {
			std::cout << "\nInvalid user name or password. Try again\n\n";
			continue;
		}
		const UserModel& user_exist = userame_userobject_map[current_user.get_user_name()];

		if (current_user.get_password() != user_exist.get_password()) {
			std::cout << "\nInvalid user name or password. Try again\n\n";
			continue;
		}
		current_user = user_exist;
		break;
	}
}
void UserController::DoSignUp() {
	std::string user_name;
	while (true) {
		std::cout << "Enter user name. (No spaces): ";
		std::cin >> user_name;

		if (userame_userobject_map.count(user_name))
			std::cout << "Already used. Try again\n";
		else
			break;
	}
	// Move logic to user class, which may keep extending data members in future

	current_user.ReadUser(user_name, ++last_id);
	userame_userobject_map[current_user.get_user_name()] = current_user;

	UpdateDatabase(current_user);
}
std::pair<int, int> UserController::ReadUserId() {
	int user_id;
	std::cout << "Enter User id or -1 to cancel: ";
	std::cin >> user_id;

	if (user_id == -1)
		return std::make_pair(-1, -1);

	for (auto& pair : userame_userobject_map) {
		if (pair.second.get_user_id() == user_id)
			return std::make_pair(user_id, pair.second.get_allow_anonymous_questions());
	}

	std::cout << "Invalid User ID. Try again\n";
	return ReadUserId();
}
void UserController::UpdateDatabase(UserModel& user) {
	std::string line = user.ToString();
	std::vector<std::string> lines(1, line);
	HelperFunctions helper;
	helper.WriteFileLines("users.txt", lines);
}
void UserController::ListUsersNamesIds()const {
	for (const auto& p : userame_userobject_map)
	{
		UserModelView user_view;
		user_view.listUserNameId(p.second);
	}
}
const UserModel& UserController::GetCurrentUser() const
{
	return current_user;
}
void UserController::ResetToQuestions(const std::vector<int>& to_questions)
{
	current_user.ResetToQuestions(to_questions);
}

void UserController::ResetFromQuestions(const std::vector<std::pair<int, int>>& to_questions) {
	current_user.ResetFromQuestions(to_questions);
}

