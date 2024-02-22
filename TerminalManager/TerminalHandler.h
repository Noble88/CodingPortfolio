#ifndef TERMINALHANDLER_H
#define TERMINALHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cstdlib> // For system function
#include <algorithm> //Gives sorting Algorithms


using namespace std;
namespace fs = std::filesystem;

// Define enum for window states
enum class WindowState { MENU, PROJECTS, SORTING_OPTIONS, VIEW_OPTIONS, HELP, QUIT };

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
  //Helper Methods
  void SortProjectByFileName(bool ascending);
  void SortProjectByProjectName(bool ascending);
  void SortProjectByDateCompleted(bool ascending);

//View will change what catagory you can see at once
  void DisplayViewOptions();
  void ViewOptionsSelectionResponse(int userInput);

//Projects Window State: Displays the projects in the "projects_folder" folder
  void DisplayProjects();
  void ProjectSelectionResponse(int userInput); 
  //Helper Methods
  vector<string> GetProjectData(const string& metadataFilePath);
  void CreateProjectDataBase(const string& projectsFolderPath);
  void RunProject(int projectIndex);
  string FormatSection(string section, int characterLimit);

//Misc methods
  void BuildExecutables();
  void MiniCommit();
  void UploadToGitHub();

//Input To Action Methods
  void GenericCommands(string userInput); //This is present in every "Selection Response" and can go through the different windows
  void HandleInput(string userInput);
  void Run();

};

#endif // TERMINALHANDLER_H