#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "Translator.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


using namespace std; //IF USING STRING

class FileProcessor{
  public:
    FileProcessor();  //Constructor  
    ~FileProcessor(); //Deconstructor

    void ProcessFile(string inputFileName, string outputFileName);
};

#endif