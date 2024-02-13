#include <iostream>
#include <string>
#include <cstdlib>

class ProjectManager {
public:
    void RunProject(const std::string& projectFolderPath, const std::string& projectName) {
        // Construct the full path to the project's main.cpp
        std::string fullPath = projectFolderPath + "/" + projectName + "/main";

        // Use fullPath to execute the project
        int result = std::system(fullPath.c_str());

        // Check the result for any errors
        if (result != 0) {
            std::cerr << "Error executing project: " << projectName << std::endl;
        }
    }
};

int main() {
    ProjectManager manager;

    // Hardcode the path to your projects folder
    std::string projectsFolderPath = "/home/runner/CodingPortfolio";

    // Run the "Hello, World!" program in Project1
    manager.RunProject(projectsFolderPath, "Project1");

    return 0;
}
