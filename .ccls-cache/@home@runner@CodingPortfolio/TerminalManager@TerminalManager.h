#ifndef TERMINALHANDLER_H
#define TERMINALHANDLER_H

#include <string>

class TerminalHandler {

public:
  TerminalHandler(){}

  void Run();
  void DisplayMainMenu();
  void DisplayLectures(); // Display should look like: Lecture 1 - [# Entrie(s)]
  void DisplayContentsOfLecture(int lectureNum); //display specfifc lecture contents
  void DisplayHelp(); //Used to give the user list of commands and other aid
  void DisplaySortingOptions();

  void InteractionFlow();
  void GenericCommands(std::string userInput); //This is present in every "Selection Responce" and can go through the different windows 
  void MainMenuSelectionResponce(std::string userInput);
  void LectureSelectionResponce(std::string userInput);
  void ContentSelectionResponce(int lectureNum, std::string userInput);
  void HelpSelectionResponce(std::string userInput);
  void SortingOptionsSelectionResponce(std::string userInput);

  void WindowSwitcher(std::string windowState); //Will switch the states the user can go through and returns the state the user is in

  std::string CleanUserInput(std::string userInput);
  std::string GetUserInput();
  // ADD OTHER METHODS HERE
};

#endif // TERMINALHANDLER_H