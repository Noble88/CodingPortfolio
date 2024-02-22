#include "TerminalHandler.h"
#include "../Resources/Debugger/Debugger.h"

// TODO: There is layering, REDO HOW TERMINAL INTERACTIONS SO THAT WHEN QUITTING
// TODO: [Add debugger for this file]
// WONT GIVE "ERROR: Invalid Window State - attempted to enter state: N/A"

TerminalHandler::TerminalHandler() {
    currentState = WindowState::MENU;
    // Initialize other member variables
}

const int MAX_PROJECTS = 100; // Maximum number of projects
const int NUM_COLUMNS = 5;     // Number of columns
string projectDisplayFormat; // [minimal], [show all]
std::string projectTable[MAX_PROJECTS][NUM_COLUMNS]; //Array that holds project data
bool projectVisibilityToggle[NUM_COLUMNS];
int projectSpacing[NUM_COLUMNS];
string projectSectionNames[NUM_COLUMNS] = {"File Name","Project Name","Project Type","Date Completed","Description"};

//Input Helper Methods
std::string TerminalHandler::CleanUserInput(string userInput) {
  std::string cleanedInput;

  // Connvert responce to lowercase & Check Character Limit
  for (char c : userInput) {
    if (std::isalnum(static_cast<unsigned char>(c))) {
      cleanedInput += std::tolower(static_cast<unsigned char>(c));
      if (cleanedInput.length() == 100) {//TODO: This is hardcoded!!! Make a system where user or debugger sets this value
        cout << "Input is over the character limit! Please limiti responces to less than 150 characters";
        break; // Stop processing if the maximum length is reached
      }
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
      return -1;
    }
    return selection;
}


//>Menu< Display & Responce
void TerminalHandler::DisplayMainMenu() {
  cout << "[MAIN MENU] \n"
      << "1) View Projects \n"
      << "2) Sorting Options\n"
      << "3) Project Viewing Options\n"
      << "4) Build All Executables\n"
        << "Option Number or General Command: ";
}
void TerminalHandler::MainMenuSelectionResponse(int userInput){
  switch (userInput){
    case 1: currentState = WindowState::PROJECTS; break;
    case 2: currentState = WindowState::SORTING_OPTIONS; break;
    case 3: currentState = WindowState::VIEW_OPTIONS; break;
    case 4: BuildExecutables(); break;
  }
}


//>Help< Display
void TerminalHandler::DisplayHelp() {
  cout << "[HELP]\n"
    <<"General Commands: [help], [menu], [projects], [sorting options] [view options] [build] [quit]\n"
    <<"Prompt Help: your input will be cleane, so any white space, special symbol, or capatalization will be ignored\n"
      << "Option Number or Command:";
}
void TerminalHandler::HelpSelectionResponse(int userInput){}


//>Sorting Options< Display & Responce
string currentSortingOption=""; //Project Name | Date Completed |
  //Help Methods
void TerminalHandler::SortProjectByFileName(bool ascending){
  // Define a struct to hold project information
    struct ProjectInfo {
      std::string projectName;
      int originalPlacement;
    };

    // Method to build ProjectInfo struct
    auto buildProjectInfo = [this](int index) {
      ProjectInfo project;
      project.projectName = projectTable[index][0];
      project.originalPlacement = index;
      return project;
    };

    // Create a vector of ProjectInfo
    std::vector<ProjectInfo> projects;
    for (int i = 0; i < MAX_PROJECTS; ++i) {
      if (!projectTable[i][0].empty()) { // Check if the project name is not empty
        projects.push_back(buildProjectInfo(i));
      }
    }

    // Sort the projects vector by project name
    std::sort(projects.begin(), projects.end(),
        [ascending](const ProjectInfo& a, const ProjectInfo& b) {
          if (ascending)
            return a.projectName < b.projectName;
          else
            return a.projectName > b.projectName;
        });

    // Rearrange the projectTable array based on the sorted project names
    std::string newProjectTable[MAX_PROJECTS][NUM_COLUMNS];
    for (size_t i = 0; i < projects.size(); ++i) {
      int originalIndex = projects[i].originalPlacement;
      for (int j = 0; j < NUM_COLUMNS; ++j) {
        newProjectTable[i][j] = projectTable[originalIndex][j];
      }
    }

    // Update the original projectTable with the rearranged data
    std::copy(&newProjectTable[0][0], &newProjectTable[0][0] + MAX_PROJECTS * NUM_COLUMNS, &projectTable[0][0]);
  }
void TerminalHandler::SortProjectByProjectName(bool ascending) {
  // Define a struct to hold project information
  struct ProjectInfo {
    std::string projectName;
    int originalPlacement;
  };

  // Method to build ProjectInfo struct
  auto buildProjectInfo = [this](int index) {
    ProjectInfo project;
    project.projectName = projectTable[index][1];
    project.originalPlacement = index;
    return project;
  };

  // Create a vector of ProjectInfo
  std::vector<ProjectInfo> projects;
  for (int i = 0; i < MAX_PROJECTS; ++i) {
    if (!projectTable[i][1].empty()) { // Check if the project name is not empty
      projects.push_back(buildProjectInfo(i));
    }
  }

  // Sort the projects vector by project name
  std::sort(projects.begin(), projects.end(),
      [ascending](const ProjectInfo& a, const ProjectInfo& b) {
        if (ascending)
          return a.projectName < b.projectName;
        else
          return a.projectName > b.projectName;
      });

  // Rearrange the projectTable array based on the sorted project names
  std::string newProjectTable[MAX_PROJECTS][NUM_COLUMNS];
  for (size_t i = 0; i < projects.size(); ++i) {
    int originalIndex = projects[i].originalPlacement;
    for (int j = 0; j < NUM_COLUMNS; ++j) {
      newProjectTable[i][j] = projectTable[originalIndex][j];
    }
  }

  // Update the original projectTable with the rearranged data
  std::copy(&newProjectTable[0][0], &newProjectTable[0][0] + MAX_PROJECTS * NUM_COLUMNS, &projectTable[0][0]);
}
void TerminalHandler::SortProjectByDateCompleted(bool ascending) {
  /*
    // Define a lambda function for comparing dates completed
    auto compareByDate = [](const std::string& a, const std::string& b) {
        // Implement your date comparison logic here
        return a < b; // Change to a > b for descending order
    };

    // Sort the project table by date completed
    std::sort(projectTable, projectTable + MAX_PROJECTS, [compareByDate](const auto& a, const auto& b) {
        return compareByDate(a[3], b[3]);
    });
    */
}
  //Display & Responce
void TerminalHandler::DisplaySortingOptions() {
  std::cout << "[SORTING OPTIONS: Sorted by "<<currentSortingOption<<"]\n"
            << "1) Sort by File Name\n"
            << "2) Sort by Project Name\n"
            << "3) Sort by Date Completed\n"
            << "Enter option: ";
}
void TerminalHandler::SortingOptionsSelectionResponse(int userInput) {
    switch (userInput) {
      case 1: SortProjectByFileName(true); currentSortingOption="File Name"; break;
      case 2: SortProjectByProjectName(true); currentSortingOption="Project Name";
        break;
      case 3: SortProjectByDateCompleted(true); currentSortingOption="Date Completed";
        break;
      default:
        std::cout << "Invalid option.\n";
        break;
  }
}


//>ViewOptions< Display & Responce
void TerminalHandler::DisplayViewOptions(){
  cout << "[VIEWING OPTIONS] \n"
       << "Current Setting: " << projectDisplayFormat << "\n";
  for (int i = 0; i < NUM_COLUMNS; ++i) {
      cout << i + 1 << ") "<<FormatSection(projectSectionNames[i],15)<<": " << (projectVisibilityToggle[i] ? " On" : " Off") << "\n";
  }
  cout << "Option Number or General Command: ";
}
void TerminalHandler::ViewOptionsSelectionResponse(int userInput){
  if (userInput >= 1 && userInput <= NUM_COLUMNS) {
      projectVisibilityToggle[userInput - 1] = !projectVisibilityToggle[userInput - 1];
      cout << FormatSection(projectSectionNames[userInput - 1],15) << userInput << ": visibility toggled to " << (projectVisibilityToggle[userInput - 1] ? "On" : "Off") << ".\n";
  } else {
      cout << "Invalid input. Please try again.\n";
  }
}


//>Project< Display & Responce & Data Creation
  //Data Creation
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
  for(int i=0; i<NUM_COLUMNS;++i){
    if(projectData[i][0]==' '){
      projectData[i].erase(0, 1);
    }
  }
  metadataFile.close(); // Close the file

    return projectData;
}
void TerminalHandler::CreateProjectDataBase(const string& projectsFolderPath) {
  DEBUG_METHOD("CreateProjectDataBase","Creating Database of Projects");
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
    string command = "cd " + projectFolderPath + " && ./" + executableName + " && cd -";//This command cd into execacutable, runs it, then reverts back to the orginal directory
    int result = std::system(command.c_str());

    if (result != 0) { cerr << "Error executing project: " << projectTable[projectIndex][1] << endl;}
  } 
  else {cout << "Executable not found: " << projectTable[projectIndex][1] << endl;}
}
string TerminalHandler::FormatSection(string section, int characterLimit) {
  std::string formattedSection;

  if (section.length() <= characterLimit) {
      // If the section length is less than or equal to the character limit, no need to truncate
      formattedSection = section;

      // Add spaces to pad the section
      int numSpacesToAdd = characterLimit - section.length();
      for (int i = 0; i < numSpacesToAdd; ++i) {
          formattedSection += " ";
      }
  } else {
      // If the section length is greater than the character limit, truncate and add ...
      formattedSection = section.substr(0, characterLimit - 3) + "...";
  }

  return formattedSection;
}

  //Display & Responce
void TerminalHandler::DisplayProjects() {
  cout << "\n\n[PROJECTS: Sorted by "<<currentSortingOption<<"]\n";

  cout <<"|  ";
  for(int i=0; i<NUM_COLUMNS; ++i){
    if(projectVisibilityToggle[i]){
      cout << FormatSection(projectSectionNames[i], projectSpacing[i]) << " | ";
    }
  }
  cout <<"\n";
  
  for (int i = 0; i < MAX_PROJECTS; ++i) {
    if (projectTable[i][0].empty()) {
        break; // Stop if we reach an empty row
    }

    cout << i + 1 << ") ";
    for(int j=0; j<NUM_COLUMNS; ++j){
      if(projectVisibilityToggle[j]){
        cout << FormatSection(projectTable[i][j], projectSpacing[j]) << " | ";
      }
    }
    cout <<"\n";
  }
  cout << "Enter a number or General Command: ";
}
void TerminalHandler::ProjectSelectionResponse(int userInput) {
  bool isInSubMenu = true;
  while(isInSubMenu){
    cout << "\n[Selected Project: " << projectTable[(userInput-1)][1] << "]" << endl; 

    // Display project menu options
    cout << "1) Run Project" << endl;
    cout << "2) See Description" << endl;
    cout << "3) Back" << endl;

    // Get user input
    cout << "Enter your choice: ";
    int choice = GetNumberFromUserInput(GetUserInput());
    // Process user's choice

    switch (choice) {
      case 1:
        std::cout << "\n-----[Running Code...]-----\n\n";
        RunProject((userInput-1)); 
        std::cout << "\n-----[End Code...]-----\n";
        isInSubMenu = false; break;
        break;
      case 2:
        cout << projectTable[(userInput-1)][4] << endl; break;
      case 3: isInSubMenu = false; break;
      default:
          cout << "Invalid choice! Please try again." << endl; isInSubMenu = false; break;
    }
  }
}

//Building Executables
void TerminalHandler::BuildExecutables(){
  cout <<"\nAre you sure you want to build executables in all projects? (y/n): ";
  if(GetUserInput()[0] == 'y'){
    const char* command = "./build_projects.sh"; // Assuming build_projects.sh is in the current directory

    int result = std::system(command); // Run the shell script

    if (result == 0) { // Check the result of the command
        std::cout << "Build completed successfully" << std::endl;
    } else {
        std::cerr << "Error: Build failed" << std::endl;
    }
  }
  CreateProjectDataBase("projects_folder");
  cout <<"\n";
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
  else if (userInput == "view options" || userInput == "view")
    currentState = WindowState::VIEW_OPTIONS;
  else if (userInput == "build" || userInput == "build executables")
    BuildExecutables();
  else
    std::cout << "Invalid Selection - Type Help for Commands & Command Formatting";
}
void TerminalHandler::HandleInput(string userInput) {
  if(GetNumberFromUserInput(userInput)!=-1){
    int numberInput = GetNumberFromUserInput(userInput);
    switch (currentState) {
        case WindowState::MENU: 
          MainMenuSelectionResponse(numberInput); break;
        case WindowState::PROJECTS: 
          ProjectSelectionResponse(numberInput); break;
        case WindowState::SORTING_OPTIONS:
          SortingOptionsSelectionResponse(numberInput);break;
        case WindowState::HELP: 
          HelpSelectionResponse(numberInput); break;
        case WindowState::VIEW_OPTIONS: 
          ViewOptionsSelectionResponse(numberInput); break;
        case WindowState::QUIT:
          /*Main loop checks currentState == quit & leaves loop so no code needed*/ break;
    }
  }
  else{GenericCommands(userInput);}
}

void TerminalHandler::Run() {
//Inital Text and Process
  cout 
    << "WELCOME TO MY C++ PORTFOLIO\n"
    << "Please type the command \"help\" for any assistence.\n";
  
  currentState = WindowState::MENU;
  CreateProjectDataBase("projects_folder");
  projectVisibilityToggle[0] = true; //File Name
  projectVisibilityToggle[1] = true; //Project Name
  projectVisibilityToggle[2] = true; //Project Type
  projectVisibilityToggle[3] = true; //Completed Date
  projectVisibilityToggle[4] = false; //Description 

  projectSpacing[0] = 25; //File Name
  projectSpacing[1] = 25; //Project Name
  projectSpacing[2] = 25; //Project Type
  projectSpacing[3] = 15; //Completed Date
  projectSpacing[4] = 100; //Description 
  
  while (currentState != WindowState::QUIT) {

    switch (currentState) {
      case WindowState::MENU: DisplayMainMenu(); break;
      case WindowState::PROJECTS: DisplayProjects(); break;
      case WindowState::SORTING_OPTIONS: DisplaySortingOptions(); break;
      case WindowState::VIEW_OPTIONS: DisplayViewOptions(); break;
      case WindowState::HELP: DisplayHelp(); break;
      default:  break;
    }
    HandleInput(GetUserInput());
    cout <<"\n";
  }
}
