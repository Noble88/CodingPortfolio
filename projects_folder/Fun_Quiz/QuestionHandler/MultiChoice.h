#ifndef MULTICHOICE_H
#define MULTICHOICE_H

#include "Question.h"
#include <vector>

class MultiChoice : public Question {
public:
    MultiChoice(string questionText, vector<string> options, string correctAnswerText, string answerExplanationText);
    ~MultiChoice();

    virtual string GetFormattedQuestions() override;

  private:
    vector<string> userOptions;
};

#endif // MULTICHOICE_H
