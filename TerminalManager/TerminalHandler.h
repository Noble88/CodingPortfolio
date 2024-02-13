#ifndef TERMINALHANDLER_H
#define TERMINALHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <experimental/filesystem>
#include <cstdlib>

using namespace std;
namespace fs = std::filesystem;

// Define enum for window states
enum class WindowState { MENU, PROJECTS, SORTING_OPTIONS, HELP, QUIT };

class TerminalHandler {
  private:
    WindowState currentState;
    // Other member variables as needed

public:
  TerminalHandler();

//Input Helper Methods
  string GetUserInput();
  string CleanUserInput(string userInput);
  int GetNumberFromUserInput(string userInput);


//Menu is the first thing displayed
  void DisplayMainMenu();
  void MainMenuSelectionResponse(int userInput);


//Help Window State: Give the user list of commands and other aid 
  void DisplayHelp(); 
  void HelpSelectionResponse(int userInput);


//Sorting Options will effect how the projects a displayed (by date, name, etc)
  void DisplaySortingOptions();
  void SortingOptionsSelectionResponse(int userInput);


//Projects Window State: Displays the projects in the "projects_folder" folder
  vector<string> GetProjectData(const string& metadataFilePath);
  void CreateProjectDataBase(const string& projectsFolderPath);
  void RunProject(int projectIndex);

  void DisplayProjects();
  void ProjectSelectionResponse(int userInput); 


//Input To Action Methods
  void GenericCommands(string userInput); //This is present in every "Selection Response" and can go through the different windows
  void HandleInput(string userInput);
  void Run();

};

#endif // TERMINALHANDLER_H