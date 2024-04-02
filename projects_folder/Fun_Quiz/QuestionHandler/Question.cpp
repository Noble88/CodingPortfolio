#include "Question.h"

Question::Question(string questionText, string correctAnswerText, string answerExplanationText){
  question=questionText;
  correctAnswer=correctAnswerText;
  answerExplanation=answerExplanationText;
}

Question::~Question(){
  
}

string Question::GetFormattedQuestions(){
  cout << "ERROR Method is being called on a Raw Question Object"<<endl;
  return "-1";
}

bool Question::CheckAnswerCorrect(string userInput){

}

string Question::GetAnswer(){
  
}

