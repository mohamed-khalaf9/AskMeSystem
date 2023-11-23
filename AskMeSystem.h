#ifndef ASKMESYSTEM_H
#define ASKMESYSTEM_H

#include "HelperFunctions.h"
#include "QuestionController.h"
#include "UserController.h"
#include "QuestionController.h"



class AskMeSystem {
private:
    QuestionController question_controller;
    UserController user_controller;

public:
    AskMeSystem();
    void ResetCurrentUserQuestions();
    void LoadDatabase(bool fill_user_questions = false);
    void run();


};

#endif