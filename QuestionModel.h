#ifndef QUESTIONMODEL_H
#define QUESTIONMODEL_H

#include "HelperFunctions.h"
#include <string>


class QuestionModel {
private:

    int question_id;
    int parent_question_id;
    int from_user_id;
    int to_user_id;
    int is_anonymous_question;
    std::string question_text;
    std::string answer_text;

public:
    QuestionModel();
    QuestionModel(std::string line);
    const int& get_question_id()const;
    const int& get_parent_question_id()const;
    const int& get_from_user_id()const;
    const int& get_to_user_id()const;
    const int& get_is_anonymous_question()const;
    const std::string& get_question_text()const;
    const std::string& get_answer_text()const;
    void set_question_id(const int& question_id_);
    void set_parent_question_id(const int& parent_q_id_);
    void set_from_user_id(const int& from_user_id_);
    void set_to_user_id(const int& to_user_id_);
    void set_is_anonymous_question(const int& is_anonymous_question_);
    void set_answer_text(const std::string& answer_text_);
    void set_question_text(const std::string& question_text_);
    std::string ToString();









};
















#endif
