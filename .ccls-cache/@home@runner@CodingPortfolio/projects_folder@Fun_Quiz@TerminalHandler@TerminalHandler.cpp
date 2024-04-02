#include "TerminalHandler.h"


std::string TerminalHandler::GetUserInput() {
    string userInput;
    cout << "Your answer: ";
    getline(std::cin, userInput);
    return userInput;
}
