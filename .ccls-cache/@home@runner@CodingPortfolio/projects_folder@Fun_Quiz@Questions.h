#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <iostream>
#include <string>
using namespace std;

class Questions{
  public:
    Questions(string question, string correctAnswer, string answerExplanation);
    ~Questions();

    string GetAnswer();
    string GetFormattedQuestions();
    bool CheckAnswerCorrect(string userInput);

  protected:
    
};

#endif