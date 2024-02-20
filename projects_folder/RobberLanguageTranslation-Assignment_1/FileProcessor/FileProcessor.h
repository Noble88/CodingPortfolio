#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "../Translator/Translator.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileProcessor{
  public:
    FileProcessor();  //Constructor  
    ~FileProcessor(); //Deconstructor

    void ProcessFile(string inputFileName, string outputFileName);
};

#endif