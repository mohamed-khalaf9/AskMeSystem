#include "UserModel.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <assert.h>
#include <sstream>



UserModel::UserModel() : user_id(-1), allow_anonymous_questions(-1) {
}

UserModel::UserModel(std::string line) {
    HelperFunctions helper;
    std::vector<std::string> substrs = helper.SplitString(line);
    assert(substrs.size() == 6);
    user_id = helper.ToInt(substrs[0]);
    user_name = substrs[1];
    password = substrs[2];
    name = substrs[3];
    email = substrs[4];
    allow_anonymous_questions = helper.ToInt(substrs[5]);
}
void UserModel::ReadUser(const std::string& user_name, int id) {
    set_user_name(user_name);
    set_user_id(id);

    std::string str;

    std::cout << "Enter password: ";
    std::cin >> str;
    set_password(str);

    std::cout << "Enter name: ";
    std::cin >> str;
    set_name(str);

    std::cout << "Enter email: ";
    std::cin >> str;
    set_email(str);

    std::cout << "Allow anonymous questions? (0 or 1): ";
    int st;
    std::cin >> st;
    set_allow_anonymous_questions(st);
}
void UserModel::ResetToQuestions(const std::vector<int>& to_questions)
{
    questions_id_from_me.clear();

    for (const auto& question_id : to_questions)
        questions_id_from_me.push_back(question_id);
}
void UserModel::ResetFromQuestions(const std::vector<std::pair<int, int>>& to_questions) {
    questionid_questionidsThead_to_map.clear();

    for (const auto& id_pair : to_questions)
        questionid_questionidsThead_to_map[id_pair.first].push_back(id_pair.second);
}
const int& UserModel::get_user_id()const {
    return user_id;
}
const std::string& UserModel::get_user_name()const {
    return user_name;
}
const std::string& UserModel::get_password()const {
    return password;
}
const int& UserModel::get_allow_anonymous_questions()const {
    return allow_anonymous_questions;
}
const std::string& UserModel::get_name()const
{
    return name;
}
const std::string& UserModel::get_email()const {
    return email;
}
const std::vector<int>& UserModel::get_questions_id_from_me()const {
    return questions_id_from_me;
}
const std::map<int, std::vector<int>>& UserModel::get_questionid_questionidsThead_to_map()const {
    return questionid_questionidsThead_to_map;
}
void UserModel::set_user_id(const int& user_id_) {
    user_id = user_id_;
}
void UserModel::set_user_name(const std::string& user_name_)
{
    user_name = user_name_;
}
void UserModel::set_password(const std::string& password_) {
    password = password_;
}
void UserModel::set_name(const std::string& name_) {
    name = name_;
}
void UserModel::set_email(const std::string& email_) {
    email = email_;
}
void UserModel::set_allow_anonymous_questions(const int& allow_anonymous_question_)
{
    allow_anonymous_questions = allow_anonymous_question_;
}
std::string UserModel::ToString()
{
    std::ostringstream oss;
    oss << user_id << "," << user_name << "," << password << "," << name << "," << email << "," << allow_anonymous_questions;

    return oss.str();
}