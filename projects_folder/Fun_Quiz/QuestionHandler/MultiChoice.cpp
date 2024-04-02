#include "MultiChoice.h"

MultiChoice::MultiChoice(string questionText, vector<string> options, string correctAnswerText, string answerExplanationText)
    :Question(questionText, correctAnswerText, answerExplanationText) {
      userOptions = options;
    }

MultiChoice::~MultiChoice() {}

string MultiChoice::GetFormattedQuestions() {
  string questionStr = question+"\n";
  
  for (size_t i = 0; i < userOptions.size(); ++i) {
      questionStr += to_string(i + 1) + ". " + userOptions[i] + "\n"; // Display option number (1-based index)
  }

  return questionStr;
}
