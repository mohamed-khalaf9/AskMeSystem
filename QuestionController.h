#ifndef QUESTIONCONTROLLER_H
#define QUESTIONCONTROLLER_H


#include "UserModel.h"
#include "QuestionModel.h"
#include "HelperFunctions.h"
#include "QuestionModelView.h"
#include <map>
#include <vector>




class QuestionController {
private:
    std::map<int, std::vector<int>> questionid_questionidsThead_to_map;
    std::map<int, QuestionModel> questionid_questionobject_map;
    int last_id;

public:
    QuestionController();
    void LoadDatabase();
    std::vector<int> GetUserToQuestions(const UserModel& user) const;
    std::vector<std::pair<int, int>> GetUserFromQuestions(const UserModel& user) const;
    int ReadQuestionIdAny(const UserModel& user);
    int ReadQuestionIdThread(const UserModel& user);
    void AnswerQuestion(const UserModel& user);
    void DeleteQuestion(const UserModel& user);
    void AskQuestion(const UserModel& user, std::pair<int, int> to_user_pair);
    void ListFeed();
    void UpdateDatabase();
    void PrintUserToQuestions(const UserModel& user);
    void PrintUserFromQuestions(const UserModel& user);



































};



























#endif