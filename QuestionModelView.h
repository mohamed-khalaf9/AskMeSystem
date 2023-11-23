#ifndef QUESTIONMODELVIEW_H
#define QUESTIONMODELVIEW_H


#include "QuestionModel.h"

class QuestionModelView {
public:
    QuestionModelView();
    void Print_to_Question(const QuestionModel& question)const;
    void Print_from_Question(const QuestionModel& question)const;
    void Print_feed_Question(const QuestionModel& question)const;
};


#endif