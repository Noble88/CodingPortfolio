//see slack if for test input!!!
#include "FileProcessor/FileProcessor.h"

//cd projects_folder/RobberLanguageTranslation-Assignment_1/RobberLanguageTranslation-Assignment_1_Executable


std::string basePath = "./projects_folder/RobberLanguageTranslation-Assignment_1/"; //This is if the main running the executable is outside of the project's scope/folder
int main() {
  FileProcessor fileProcessor;
  fileProcessor.ProcessFile(basePath+"Txt_and_HTML/EnglishEntry.txt", basePath+"Txt_and_HTML/HTMLFormat.html");
  
  //This is for inside my coding portfolio project
  
  
  return 0;
}