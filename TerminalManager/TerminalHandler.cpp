#include "TerminalHandler.h"
#include <iostream>


// TODO: There is layering, REDO HOW TERMINAL INTERACTIONS SO THAT WHEN QUITTING
// TODO: [Add debugger for this file]
// WONT GIVE "ERROR: Invalid Window State - attempted to enter state: N/A"

TerminalHandler::TerminalHandler() {
    currentState = WindowState::MENU;
    // Initialize other member variables
}

//Input Helper Methods
std::string TerminalHandler::CleanUserInput(string userInput) {
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
string TerminalHandler::GetUserInput() {
  std::string userInput;
  std::cin >> userInput;
  return CleanUserInput(userInput);
}
int TerminalHandler::GetNumberFromUserInput(string userInput) {
    int selection = -1;
    try {
        selection = std::stoi(userInput); // Convert string to int
    } catch (const std::invalid_argument &e) { //No number means 
      GenericCommands(userInput); 
      return -1;
    }
    return selection;
}


//>Menu< Display & Responce
void TerminalHandler::DisplayMainMenu() {
  cout << "[MAIN MENU] \n"
      << "1) View Projects \n"
      << "2) Sorting Options (unavailable) \n"
        << "Option Number or General Command: ";
}
void TerminalHandler::MainMenuSelectionResponse(int userInput){
  switch (userInput){
    case 1: currentState = WindowState::PROJECTS; break;
    case 2: currentState = WindowState::SORTING_OPTIONS; break;
  }
}


//>Help< Display
void TerminalHandler::DisplayHelp() {
  cout << "[HELP]\n"
    <<"General Commands: [help], [menu], [projects], [sorting options] [quit]\n"
    <<"Prompt Help: your input will be cleane, so any white space, special symbol, or capatalization will be ignored\n"
      << "Option Number or Command:";
}
void TerminalHandler::HelpSelectionResponse(int userInput){}


//>Sorting Options< Display & Responce
void TerminalHandler::DisplaySortingOptions() {
  cout 
    << "[SORTING OPTIONS}\n"
    <<" UNAVALIBLE FOR NOW!\n"
      << "General Command: ";
}
void TerminalHandler::SortingOptionsSelectionResponse(int userInput) {}


//>Project< Display & Responce
  //File Managment & Data Creation
const int MAX_PROJECTS = 100; // Maximum number of projects
const int NUM_COLUMNS = 5;     // Number of columns

std::string projectTable[MAX_PROJECTS][NUM_COLUMNS]; //Array that holds project data

vector<string> TerminalHandler::GetProjectData(const string& metadataFilePath) {
    vector<string> projectData;
    ifstream metadataFile(metadataFilePath);
    string line;

    // Initialize project data with empty strings
    projectData.resize(NUM_COLUMNS);

    // Read metadata file line by line
    while (getline(metadataFile, line)) {
        if (line.find("Project Name:") != string::npos) {
            projectData[1] = line.substr(line.find(":") + 1);
        } else if (line.find("Project Type:") != string::npos) {
            projectData[2] = line.substr(line.find(":") + 1);
        } else if (line.find("Completed Date:") != string::npos) {
            projectData[3] = line.substr(line.find(":") + 1);
        } else if (line.find("Description:") != string::npos) {
            projectData[4] = line.substr(line.find(":") + 1);
        }
    }
    metadataFile.close(); // Close the file

    return projectData;
}
void TerminalHandler::CreateProjectDataBase(const string& projectsFolderPath) {
    int projectCount = 0;

    for (const auto& entry : fs::directory_iterator(projectsFolderPath)) {
        if (entry.is_directory()) {
            string projectFolder = entry.path().filename();
            string metadataFilePath = entry.path() / "metadata.txt";

            // Check if metadata.txt exists for this project
            if (fs::exists(metadataFilePath)) {
                // Extract project data
                vector<string> projectData = GetProjectData(metadataFilePath);

                // Assign project data to the project table
                projectTable[projectCount][0] = projectFolder; // Exact File Name
                projectTable[projectCount][1] = projectData[1]; // Project Name
                projectTable[projectCount][2] = projectData[2]; // Project Type
                projectTable[projectCount][3] = projectData[3]; // Completed Date
                projectTable[projectCount][4] = projectData[4]; // Description

                projectCount++;
            }
        }
    }
}
void TerminalHandler::RunProject(int projectIndex) {
  string executableName = projectTable[projectIndex][0] + "_Executable";
  string projectFolderPath = "projects_folder/" + projectTable[projectIndex][0];
  string fullPath = projectFolderPath + "/" + executableName;

  if (fs::is_regular_file(fullPath)) {
    int result = std::system(fullPath.c_str());

    if (result != 0) {
      cerr << "Error executing project: " << projectTable[projectIndex][1] << endl;
    }
  } else {
      cout << "Executable not found: " << projectTable[projectIndex][1] << endl;
  }
}

//Basic Stuff
void TerminalHandler::DisplayProjects() {
  cout << "\n\n[PROJECTS]\n";
  
  for (int i = 0; i < MAX_PROJECTS; ++i) {
    if (projectTable[i][0].empty()) {
        break; // Stop if we reach an empty row
    }
    cout << i + 1 << ") " 
      << projectTable[i][1] << " | " //"Project Name
      << projectTable[i][2]  << " | " //"Project Type
      << projectTable[i][3] << " | \n"; // Completed Date
  }
  
  if(false){//Display All Data
    for (int i = 0; i < MAX_PROJECTS; ++i) {
        if (projectTable[i][0].empty()) {
            break; // Stop if we reach an empty row
        }

        // Print project data
        cout << "Project " << (i + 1) << ":" << endl;
        cout << "Exact File Name: " << projectTable[i][0] << endl;
        cout << "Project Name: " << projectTable[i][1] << endl;
        cout << "Project Type: " << projectTable[i][2] << endl;
        cout << "Completed Date: " << projectTable[i][3] << endl;
        cout << "Description: " << projectTable[i][4] << endl;
        cout << endl;
    }
  }


  
  
/*
  // Assuming all project folders are directly under the projects_folder
  std::string projectsFolderPath =
      "/home/runner/CodingPortfolio/projects_folder";

  std::vector<std::string> projectNames; // Store project names for selection
  std::vector<std::string> projectDescriptions; // Store project descriptions

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

        std::string metadataString; // To store all components on one line
        std::string description;    // To store the description

        while (std::getline(metadataFile, line)) {
          if (line.find("Description:") != std::string::npos) {
            description = line.substr(line.find(":") + 1);
          } else {
            metadataString += line + " | ";
          }
        }

        // Remove the trailing " | "
        if (!metadataString.empty()) {
          metadataString =
              metadataString.substr(0, metadataString.length() - 3);
        }

        // Display the components
        std::cout << ++projectCount << ") " << metadataString << std::endl;

        // Store the description
        projectDescriptions.push_back(description);

        metadataFile.close();
      } else {
        std::cout << ++projectCount << ") " << projectFolder
                  << " | Metadata not found" << std::endl;

        // Store an empty description for projects without metadata
        projectDescriptions.push_back("");
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
      bool subSelection = true;
      while (subSelection) {
        std::cout << "\n[" << selectedProjectName << "]\n";
        std::cout << "1) Run Project\n";
        std::cout << "2) See Description\n";
        std::cout << "3) Back\n";
        std::cout << "Select an Option: ";
        std::string optionInput = GetUserInput();
        if (optionInput == "1") {
          subSelection = false;
          
          ProjectSelectionResponse(selectedProjectName);

          break;
        } else if (optionInput == "2") {
          // Display the stored description for the selected project
          std::cout << "Description: "
                    << projectDescriptions[selectedProjectIndex - 1] << "\n";
        } else if (optionInput == "3") {
          DisplayProjects();
          break;
        }
      }
      WindowSwitcher("projects");
    } else {
      // Invalid project number, fall back to generic commands
      GenericCommands(userInput);
    }
  } catch (const std::invalid_argument &e) {
    // User didn't enter a valid number, fall back to generic commands
    GenericCommands(userInput);
  }
  */
}
void TerminalHandler::ProjectSelectionResponse(int userInput) {
  bool isInSubMenu = true;
  while(isInSubMenu){
    cout << "\n[Selected Project: " << projectTable[userInput][1] << "]" << endl; 

    // Display project menu options
    cout << "Project Menu:" << endl;
    cout << "1) Run Project" << endl;
    cout << "2) See Description" << endl;
    cout << "3) Back" << endl;

    // Get user input
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    // Process user's choice

    switch (choice) {
      case 1:
        std::cout << "\n-----[Running Code...]-----\n";
        RunProject(userInput); 
        std::cout << "\n-----[End Code...]-----\n";
        isInSubMenu = false; break;
        break;
      case 2:
        cout << projectTable[userInput][4] << endl; break;
      case 3: isInSubMenu = false; break;
      default:
          cout << "Invalid choice! Please try again." << endl;
          break;
    }
  }


}


//Input To Action Methods
void TerminalHandler::GenericCommands(string userInput) {
  if (userInput == "menu" || userInput == "main menu")
    currentState = WindowState::MENU;
  else if (userInput == "project" || userInput == "projects")
    currentState = WindowState::PROJECTS;
  else if (userInput == "sorting options" || userInput == "sorting" ||
           userInput == "sort" || userInput == "filter")
    currentState = WindowState::SORTING_OPTIONS;
  else if (userInput == "help")
    currentState = WindowState::HELP;
  else if (userInput == "quit" || userInput == "exit" || userInput == "q")
    currentState = WindowState::QUIT;
  else
    std::cout << "Invalid Selection - Type Help for Commands & Command Formatting";
}
void TerminalHandler::HandleInput(string userInput) {
  switch (currentState) {
      case WindowState::MENU: 
        MainMenuSelectionResponse(GetNumberFromUserInput(userInput)); break;
      case WindowState::PROJECTS: 
        ProjectSelectionResponse(GetNumberFromUserInput(userInput)); break;
      case WindowState::SORTING_OPTIONS:
        SortingOptionsSelectionResponse(GetNumberFromUserInput(userInput));break;
      case WindowState::HELP: 
        HelpSelectionResponse(GetNumberFromUserInput(userInput)); break;
      case WindowState::QUIT:
        /*Main loop checks currentState == quit & leaves loop so no code needed*/ break;
  }
}

void TerminalHandler::Run() {

//Inital Text and Process
  cout 
    << "WELCOME TO MY C++ PORTFOLIO\n"
    << "Please type the command \"help\" for any assistence.";
  currentState = WindowState::MENU;
  CreateProjectDataBase("projects_folder");
  
  while (currentState != WindowState::QUIT) {
    switch (currentState) {
      case WindowState::MENU: DisplayMainMenu(); break;
      case WindowState::PROJECTS: DisplayProjects(); break;
      case WindowState::SORTING_OPTIONS: DisplaySortingOptions(); break;
      case WindowState::HELP: DisplayHelp(); break;
      default:  break;
    }

    HandleInput(GetUserInput());
  }
}
