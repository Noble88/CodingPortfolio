#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>
#include <string>
using namespace std;

class Question{
  public:
    Question(string questionText, string correctAnswerText, string answerExplanationText);
    virtual ~Question();

    virtual string GetFormattedQuestions();
    virtual bool CheckAnswerCorrect(string userInput);
    string GetAnswer();

    


  protected:
    string question;
    string correctAnswer;
    string answerExplanation;
    
};

#endif