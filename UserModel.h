#ifndef USERMODEL_H
#define USERMODEL_H


#include "HelperFunctions.h"
#include <string>
#include <map>
#include <vector>




class UserModel {
private:
    int user_id;		// internal system ID
    std::string user_name;
    std::string password;
    std::string name;
    std::string email;
    int allow_anonymous_questions;	// 0 or 1

    std::vector<int> questions_id_from_me;

    std::map<int, std::vector<int>> questionid_questionidsThead_to_map;

public:

    UserModel();
    UserModel(std::string line);
    void ReadUser(const std::string& name, int id);
    void ResetToQuestions(const std::vector<int>& to_questions);
    void ResetFromQuestions(const std::vector<std::pair<int, int>>& to_questions);
    const int& get_user_id()const;
    const std::string& get_user_name()const;
    const std::string& get_password()const;
    const std::string& get_name()const;
    const std::string& get_email()const;
    const int& get_allow_anonymous_questions()const;
    const std::vector<int>& get_questions_id_from_me()const;
    const std::map<int, std::vector<int>>& get_questionid_questionidsThead_to_map()const;
    void set_user_id(const int& user_id_);
    void set_user_name(const std::string& user_name_);
    void set_password(const std::string& password_);
    void set_name(const std::string& name_);
    void set_email(const std::string& email_);
    void set_allow_anonymous_questions(const int& allow_anonymous_question_);
    std::string ToString();





























};












#endif