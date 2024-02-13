#include "TerminalHandler.h"
#include <iostream>

std::string windowState = "N/A"; // Can be: menu, projects, sorting options,
                                 // help

void TerminalHandler::GenericCommands(std::string userInput) {
  if (userInput == "menu" || userInput == "main menu")
    WindowSwitcher("menu");
  else if (userInput == "view lecture" || userInput == "projects")
    WindowSwitcher("projects");
  else if (userInput == "sorting options" || userInput == "sorting" ||
           userInput == "sort" || userInput == "filter")
    WindowSwitcher("sorting options");
  else if (userInput == "help")
    WindowSwitcher("help");
  else
    std::cout << "Invalid Selection Type Help";
  WindowSwitcher(windowState);
}

//>Sorting Options< Display & Responce
void TerminalHandler::DisplaySortingOptions() {
  std::cout << "[SORTING OPTIONS} \n UNAVALIBLE FOR NOW!";
  std::cout << "\nGeneral Command: ";
}
void TerminalHandler::SortingOptionsSelectionResponce(std::string userInput) {
  GenericCommands(userInput);
}

//>Menu< Display & Responce
void TerminalHandler::DisplayMainMenu() {
  std::cout << "[MAIN MENU] \n1) View Projects \n2) Sorting Options (unavalible";
  std::cout << "\nOption Number or General Command: ";
}
void TerminalHandler::MainMenuSelectionResponce(std::string userInput) {
  int selection = -1;
  try {
    selection = std::stoi(userInput); // Convert string to int
  } catch (const std::invalid_argument &e) {
    GenericCommands(userInput);
  }
  switch (selection) {
  case 1:
    WindowSwitcher("projects");
    break;
  case 2:
    WindowSwitcher("sorting options");
    break;
  }
}

//>Project< Display & Responce
void TerminalHandler::DisplayProjects() {
  std::cout << "\n\n[PROJECTS]\n";

  // Assuming all project folders are directly under the projects_folder
  std::string projectsFolderPath =
      "/home/runner/CodingPortfolio/projects_folder";

  std::vector<std::string> projectNames; // Store project names for selection

  // Iterate through the project folders
  int projectCount = 0;
  for (const auto &entry :
       std::filesystem::directory_iterator(projectsFolderPath)) {
    if (entry.is_directory()) {
      std::string projectFolder = entry.path().filename();
      std::string metadataFilePath = entry.path() / "metadata.txt";

      // Check if metadata.txt exists for this project
      if (std::filesystem::exists(metadataFilePath)) {
        // Read and display the content of metadata.txt
        std::ifstream metadataFile(metadataFilePath);
        std::string line;
        std::getline(metadataFile, line); // Read the entire line
        metadataFile.close();

        // Split the line into individual components using a delimiter (e.g., comma)
        std::istringstream ss(line);
        std::vector<std::string> metadataComponents;
        std::string component;
        while (std::getline(ss, component, ',')) {
          metadataComponents.push_back(component);
        }

        // Check if there are enough components (at least 3) to display
        if (metadataComponents.size() >= 3) {
          std::cout << ++projectCount << ") " << metadataComponents[0] << " | "
                    << metadataComponents[1] << " | " << metadataComponents[2]
                    << std::endl;
        } else {
          std::cout << ++projectCount << ") " << projectFolder
                    << " | Metadata format error" << std::endl;
        }
      } else {
        std::cout << ++projectCount << ") " << projectFolder
                  << " | Metadata not found" << std::endl;
      }

      projectNames.push_back(projectFolder);
    }
  }

  std::cout
      << "\nSelect a project by entering its number or type a General Command:";

  std::string userInput;
  userInput = GetUserInput(); // This cleans user input

  int selectedProjectIndex = -1;

  try {
    selectedProjectIndex = std::stoi(userInput);

    if (selectedProjectIndex >= 1 && selectedProjectIndex <= projectCount) {
      // User selected a project by number
      std::string selectedProjectName = projectNames[selectedProjectIndex - 1];
      ProjectSelectionResponse(selectedProjectName);
    } else {
      // Invalid project number, fall back to generic commands
      GenericCommands(userInput);
    }
  } catch (const std::invalid_argument &e) {
    // User didn't enter a valid number, fall back to generic commands
    GenericCommands(userInput);
  }
}
void TerminalHandler::ProjectSelectionResponse(const std::string &userInput) {
  // Check if userInput is a valid project name
  std::string projectsFolderPath =
      "/home/runner/CodingPortfolio/projects_folder";

  // Check if the user input corresponds to a project folder
  std::string projectFolderPath = projectsFolderPath + "/" + userInput;

  // Construct the correct executable name based on the folder name
  std::string executableName = userInput + "_Executable";

  // Construct the full path to the executable
  std::string fullPath = projectFolderPath + "/" + executableName;

  if (std::filesystem::is_regular_file(fullPath)) {
    // Use fullPath to execute the project
    int result = std::system(fullPath.c_str());

    // Check the result for any errors
    if (result != 0) {
      std::cerr << "Error executing project: " << userInput << std::endl;
    }
  } else {
    std::cout << "Executable not found: " << userInput << std::endl;
  }

  // After running the project, you can return to the main menu or provide other
  // options
  WindowSwitcher("menu");
}


// MISC
void TerminalHandler::DisplayHelp() {
  std::cout << "[HELP]\nGeneral Commands: [help], [menu], [projects], [sorting "
               "options]\nPrompt Help: you answered a cleared up so any white "
               "space, special symbol, or capatalization will be ignored";
  std::cout << "\nOption Number or Command:";
}

std::string TerminalHandler::CleanUserInput(std::string userInput) {
  std::string cleanedInput;

  // Connvert responce to lowercase
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

std::string TerminalHandler::GetUserInput() {
  std::string userInput;
  std::cin >> userInput;
  return CleanUserInput(userInput);
}

void TerminalHandler::WindowSwitcher(std::string windowState) {
  std::cout << "\n\n";
  std::string userInput;
  if (windowState == "menu") {
    std::string windowState = "menu";
    DisplayMainMenu();
    userInput = GetUserInput();
    MainMenuSelectionResponce(userInput);

  } else if (windowState == "projects") {
    std::string windowState = "projects";
    DisplayProjects();
  }

  else if (windowState == "sorting options") {
    std::string windowState = "sorting options";
    DisplaySortingOptions();
    userInput = GetUserInput();
    SortingOptionsSelectionResponce(userInput);

  } else if (windowState == "help") {
    std::string windowState = "help";
    DisplayHelp();
    userInput = GetUserInput();
    GenericCommands(userInput);
  } else
    std::cout << "ERROR: Invalid Window State - attempted to enter state: " +
                     windowState;
  ;
  std::cout << "\n\n";
}

void TerminalHandler::Run() {
  std::cout << "WELCOME TO MY C++ PORTFOLIO\nPlease type the command \"help\" "
               "for any assistence.";
  WindowSwitcher("menu");
}

/*
//>projects< Display & Responce
void TerminalHandler:: DisplayLectures(){
  std::cout << "[LECTURES]\n";
  for (int row = 0; row < manager.numberOfLectures; row++) {
    std::cout << "Lecture ";
    std::cout << std::to_string(row+1);
    if( (row+1) < 10 ) std::cout << +" "; //Add a space for 1 digit numbers

    std::cout << " - ["+ std::to_string(manager.codeHolder[row].size()) +"
Entrie(s)]" << std::endl;
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
  for (int contentNum = 0; contentNum < manager.codeHolder[lectureNum-1].size();
contentNum++) { std::unique_ptr<ClassCode>& contentObj =
manager.codeHolder[lectureNum - 1][contentNum]; std::cout <<
std::to_string(contentNum+1)+") "
      +"Name: "+contentObj->assignmentName <<
      +" | Type: "+contentObj->type
      +" | Date Completed: "+contentObj->dateCompleted << std::endl;
  }
  std::cout << "\nContent Name, Number, or General Command:";
}
void TerminalHandler:: ContentSelectionResponce (int lectureNum, std::string
userInput){ int contentNumber = -1; try {contentNumber = std::stoi(userInput);
//Convert string to int } catch (const std::invalid_argument& e) {
    GenericCommands(userInput);
  }
  if(contentNumber>0 && contentNumber<=manager.codeHolder[lectureNum -
1].size()){ std::cout << "\n[RUNNING "+ manager.codeHolder[lectureNum -
1][contentNumber-1]->type+": "+ manager.codeHolder[lectureNum -
1][contentNumber-1]->assignmentName+"]\n";
      "Description:"+manager.codeHolder[lectureNum -
1][contentNumber-1]->description+"]\n"; manager.RunCode({lectureNum-1,
contentNumber-1});
  }
  LectureSelectionResponce(std::to_string(lectureNum));
}
*/