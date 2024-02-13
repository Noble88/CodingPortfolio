#include "TerminalHandler.h"
#include <iostream>


//TODO: There is layering, REDO HOW TERMINAL INTERACTIONS SO THAT WHEN QUITTING WONT GIVE "ERROR: Invalid Window State - attempted to enter state: N/A"

std::string windowState = "N/A"; // Can be: menu, projects, sorting options, help

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
  else if (userInput == "quit" || userInput == "exit" || userInput == "q")
    std::cout << "Exiting..." << std::endl;
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
  std::cout
      << "[MAIN MENU] \n1) View Projects \n2) Sorting Options (unavalible";
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
          std::cout << "\n-----[Running Code...]-----\n";
          ProjectSelectionResponse(selectedProjectName);
          std::cout << "\n-----[End Code...]-----\n";
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
}

// MISC
void TerminalHandler::DisplayHelp() {
  std::cout << "[HELP]\nGeneral Commands: [help], [menu], [projects], [sorting options] [quit]\nPrompt Help: your input will be cleane, so any white space, special symbol, or capatalization will be ignored";
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