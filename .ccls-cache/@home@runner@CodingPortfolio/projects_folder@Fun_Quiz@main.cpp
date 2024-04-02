#include <iostream>
#include "QuestionHandler/Question.h"
#include "QuestionHandler/MultiChoice.h"

int main() {
    std::vector<Question*> questions;

    // Example data for a multiple choice question
    std::string mcQuestionText = "What is the capital of France?";
    std::vector<std::string> mcOptions = {"London", "Paris", "Berlin", "Rome"};
    std::string mcCorrectAnswer = "Paris";
    std::string mcAnswerExplanation = "Paris is the capital of France.";

    // Create a MultiChoice object and add it to the array
    MultiChoice* mcQuestion = new MultiChoice(mcQuestionText, mcOptions, mcCorrectAnswer, mcAnswerExplanation);
    questions.push_back(mcQuestion);

    for (const auto& question : questions) {
        std::cout << question->GetFormattedQuestions() << std::endl;
    }

    // Clean up the dynamically allocated memory
    for (const auto& question : questions) {
        delete question; // Delete the objects, not just the pointers
    }

    return 0;
}
