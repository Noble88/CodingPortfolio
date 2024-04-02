#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>
#include <string>
using namespace std;

class Question{
  public:
    Question(string question, string correctAnswer, string answerExplanation);
    ~Question();

    string GetAnswer();
    string GetFormattedQuestions();
    bool CheckAnswerCorrect(string userInput);

  protected:
    string questionText
    
};

#endif