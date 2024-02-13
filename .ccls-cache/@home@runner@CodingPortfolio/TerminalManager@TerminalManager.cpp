#include <fstream>
#include <filesystem>

#include "TerminalManager.h"
#include <iostream>
#include <string>

/*
void TerminalHandler::Run() {
    std::string userInput;
    while (true) {
        std::cout << "Enter command (run, list, exit): ";
        std::cin >> userInput;

        if (userInput == "run") {
            // Handling for 'run' command
        }
        // ... handle other commands
    }
}
*/

//TODO: add sorting method screen can chose whether to sort content data, etc.

std::string windowState="N/A"; //Can be: menu, lectures, sorting options, help

void TerminalHandler:: GenericCommands(std::string userInput){
  if(userInput == "menu" || userInput == "main menu")
    WindowSwitcher("menu");
  else if(userInput == "view lecture" || userInput == "lectures")
    WindowSwitcher("lectures");
  else if(userInput == "sorting options" || userInput == "sorting" || userInput == "sort" || userInput == "filter")
    WindowSwitcher("sorting options");
  else if(userInput == "help")
    WindowSwitcher("help");  
  else 
    std::cout<<"Invalid Selection Type Help";
  WindowSwitcher(windowState);
}

//>Sorting Options< Display & Responce
void TerminalHandler:: DisplaySortingOptions(){
  std::cout<<"[SORTING OPTIONS} \n UNAVALIBLE FOR NOW!";
  std::cout<<"\nGeneral Command: ";
}
void TerminalHandler:: SortingOptionsSelectionResponce(std::string userInput){
  GenericCommands(userInput);
}

//>Menu< Display & Responce
void TerminalHandler:: DisplayMainMenu(){
  std::cout << "[MAIN MENU] \n1) View Lecture \n2) Sorting Options (unavalible";
  std::cout << "\nOption Number or General Command: ";
}
void TerminalHandler:: MainMenuSelectionResponce(std::string userInput){
  int selection=-1;
  try {selection = std::stoi(userInput); //Convert string to int
  } catch (const std::invalid_argument& e) {
    GenericCommands(userInput);
  } 
  switch(selection){
    case 1: WindowSwitcher("lectures"); break;
    case 2: WindowSwitcher("sorting options"); break;
  }

}

//>Lectures< Display & Responce
void TerminalHandler:: DisplayLectures(){
  std::cout << "[LECTURES]\n";
  for (int row = 0; row < manager.numberOfLectures; row++) {
    std::cout << "Lecture ";
    std::cout << std::to_string(row+1);
    if( (row+1) < 10 ) std::cout << +" "; //Add a space for 1 digit numbers

    std::cout << " - ["+ std::to_string(manager.codeHolder[row].size()) +" Entrie(s)]" << std::endl;
  }
  std::cout << "\nView Lecture Number or General Commands:"; 
}
void TerminalHandler:: LectureSelectionResponce (std::string userInput){
  int lectureNumber=-1;
  try {lectureNumber = std::stoi(userInput); //Convert string to int
  } catch (const std::invalid_argument& e) {
    GenericCommands(userInput);
  }
  if(lectureNumber>0 && lectureNumber<=manager.numberOfLectures){
    DisplayContentsOfLecture(lectureNumber); 
    std::cin >> userInput; CleanUserInput(userInput);
    ContentSelectionResponce(lectureNumber, userInput);
  }
  else {WindowSwitcher("lectures");}
}

//>Content< Display & Responce
void TerminalHandler:: DisplayContentsOfLecture(int lectureNum){
  std::cout << "\n\n[LECTURE "+std::to_string(lectureNum)+" CONTENT]\n";
  for (int contentNum = 0; contentNum < manager.codeHolder[lectureNum-1].size(); contentNum++) {
    std::unique_ptr<ClassCode>& contentObj = manager.codeHolder[lectureNum - 1][contentNum];
    std::cout << std::to_string(contentNum+1)+") "
      +"Name: "+contentObj->assignmentName << 
      +" | Type: "+contentObj->type
      +" | Date Completed: "+contentObj->dateCompleted << std::endl;
  }
  std::cout << "\nContent Name, Number, or General Command:";
}
void TerminalHandler:: ContentSelectionResponce (int lectureNum, std::string userInput){
  int contentNumber = -1;
  try {contentNumber = std::stoi(userInput); //Convert string to int
  } catch (const std::invalid_argument& e) {
    GenericCommands(userInput);
  }
  if(contentNumber>0 && contentNumber<=manager.codeHolder[lectureNum - 1].size()){
    std::cout << "\n[RUNNING "+
      manager.codeHolder[lectureNum - 1][contentNumber-1]->type+": "+
      manager.codeHolder[lectureNum - 1][contentNumber-1]->assignmentName+"]\n";
      "Description:"+manager.codeHolder[lectureNum - 1][contentNumber-1]->description+"]\n";
    manager.RunCode({lectureNum-1, contentNumber-1});
  }
  LectureSelectionResponce(std::to_string(lectureNum));
}

//MISC
void TerminalHandler:: DisplayHelp(){
  std::cout << "[HELP]\nGeneral Commands: [help], [menu], [lectures], [sorting options]\nPrompt Help: you answered a cleared up so any white space, special symbol, or capatalization will be ignored";
  std::cout << "\nOption Number or Command:";
}

std::string TerminalHandler:: CleanUserInput(std::string userInput){
  std::string cleanedInput;

  //Connvert responce to lowercase
  for (char c : userInput) {
      if (std::isalnum(static_cast<unsigned char>(c))) {
          cleanedInput += std::tolower(static_cast<unsigned char>(c));
      }
  }

// Trim leading and trailing whitespace
  auto start = cleanedInput.find_first_not_of(" \t\n\r\f\v");
  if (start != std::string::npos) {
      auto end = cleanedInput.find_last_not_of(" \t\n\r\f\v");
      cleanedInput = cleanedInput.substr(start, end - start + 1);
  }
  return cleanedInput;
}

std::string TerminalHandler:: GetUserInput(){
  std::string userInput;
  std::cin >> userInput; 
  return CleanUserInput(userInput);
}

void TerminalHandler:: WindowSwitcher(std::string windowState){
  std::cout << "\n\n";
  std::string userInput;
  if(windowState == "menu"){std::string windowState="menu";
    DisplayMainMenu(); userInput = GetUserInput(); MainMenuSelectionResponce(userInput);
  }
  else if (windowState == "lectures") {std::string windowState="lectures";
    DisplayLectures(); userInput = GetUserInput(); LectureSelectionResponce(userInput);
  }

  else if (windowState == "sorting options") {std::string windowState="sorting options";
    DisplaySortingOptions(); userInput = GetUserInput(); SortingOptionsSelectionResponce(userInput);

  }
  else if (windowState == "help") {std::string windowState="help";
    DisplayHelp(); userInput = GetUserInput(); GenericCommands(userInput);
  }
  else std::cout<<"ERROR: Invalid Window State - attempted to enter state: "+windowState;;  
  std::cout << "\n\n";
}

void TerminalHandler::Run(){
  std::cout <<"WELCOME TO MY C++ PORTFOLIO\nPlease type the command \"help\" for any assistence.";
  WindowSwitcher("menu");
}

void TerminalHandler::DisplayProjectMetadata() {
    // Assuming all project folders are directly under the projects_folder
    std::string projectsFolderPath = "/home/runner/CodingPortfolio/projects_folder";

    // Iterate through the project folders
    for (const auto& entry : std::filesystem::directory_iterator(projectsFolderPath)) {
        if (entry.is_directory()) {
            std::string projectFolder = entry.path().filename();
            std::string metadataFilePath = entry.path() / "metadata.txt";

            // Check if metadata.txt exists for this project
            if (std::filesystem::exists(metadataFilePath)) {
                // Read and display the content of metadata.txt
                std::ifstream metadataFile(metadataFilePath);
                std::string line;
                while (std::getline(metadataFile, line)) {
                    std::cout << "Project: " << projectFolder << " | Metadata: " << line << std::endl;
                }
                metadataFile.close();
            } else {
                std::cout << "Project: " << projectFolder << " | Metadata not found" << std::endl;
            }
        }
    }
}
