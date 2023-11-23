#include "QuestionModel.h"
#include "HelperFunctions.h"
#include <iostream>
#include <assert.h>
#include <sstream>


QuestionModel::QuestionModel() : question_id(-1), parent_question_id(-1), from_user_id(-1), to_user_id(1),
is_anonymous_question(-1) {

}
QuestionModel::QuestionModel(std::string line) {
    HelperFunctions helper;
    std::vector<std::string> substrs = helper.SplitString(line);
    assert(substrs.size() == 7);
   
    set_question_id(helper.ToInt(substrs[0]));
    set_parent_question_id(helper.ToInt(substrs[1]));
    set_from_user_id(helper.ToInt(substrs[2]));
    set_to_user_id(helper.ToInt(substrs[3]));
    set_is_anonymous_question(helper.ToInt(substrs[4]));
    question_text = substrs[5];
    answer_text = substrs[6];
}
const int& QuestionModel::get_question_id()const {
    return question_id;

}
const int& QuestionModel::get_parent_question_id()const {
    return parent_question_id;

}
const int& QuestionModel::get_from_user_id()const {
    return from_user_id;

}
const int& QuestionModel::get_to_user_id()const {
    return to_user_id;
}
const int& QuestionModel::get_is_anonymous_question()const {
    return is_anonymous_question;
}
const std::string& QuestionModel::get_question_text()const {
    return question_text;

}
const std::string& QuestionModel::get_answer_text()const {
    return answer_text;
}
void QuestionModel::set_question_id(const int& question_id_) {
    question_id = question_id_;
}
void QuestionModel::set_parent_question_id(const int& parent_q_id_) {
    parent_question_id = parent_q_id_;
}
void QuestionModel::set_from_user_id(const int& from_user_id_) {
    from_user_id = from_user_id_;
}
void QuestionModel::set_to_user_id(const int& to_user_id_) {
    to_user_id = to_user_id_;
}
void QuestionModel::set_is_anonymous_question(const int& is_anonymous_question_) {
    is_anonymous_question = is_anonymous_question_;
}
void QuestionModel::set_answer_text(const std::string& answer_text_)
{
    answer_text = answer_text_;
}
void QuestionModel::set_question_text(const std::string& question_text_)
{
    question_text = question_text_;
}
std::string QuestionModel::ToString() {
    std::ostringstream oss;
    oss << question_id << "," << parent_question_id << "," << from_user_id << "," << to_user_id << "," << is_anonymous_question << "," << question_text << "," << answer_text;
    return oss.str();
}