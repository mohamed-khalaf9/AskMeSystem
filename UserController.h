#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H


#include "UserModel.h"
#include <map>
#include <string>







class UserController {
private:
    std::map<std::string, UserModel> userame_userobject_map;
    int last_id;
    UserModel current_user;

public:

    UserController();
    void LoadDatabase();
    void AccessSystem();
    void DoLogin();
    void DoSignUp();
    std::pair<int, int> ReadUserId();
    void UpdateDatabase(UserModel& user);
    void ListUsersNamesIds()const;
    const UserModel& GetCurrentUser() const;
    void ResetToQuestions(const std::vector<int>& to_questions);
    void ResetFromQuestions(const std::vector<std::pair<int, int>>& to_questions);























};






















#endif