//see slack if for test input!!!
#include "FileProcessor/FileProcessor.h"

//cd -> projects_folder/RobberLanguageTranslation-Assignment_1/main.cp

int main() {
  FileProcessor fileProcessor;
  fileProcessor.ProcessFile("Txt_and_HTML/EnglishEntry.txt", "Txt_and_HTML/HTMLFormat.html");
  return 0;
}