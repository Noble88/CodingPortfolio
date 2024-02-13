#ifndef TEXTANALYZER_H
#define TEXTANALYZER_H 

#include <iostream>
#include <string>

using namespace std;

class TextAnalyzer{
  public:
    TextAnalyzer();  //Constructor
    ~TextAnalyzer(); //Deconstructor
    int countVowels(std::string strContent);

    //Any Methods Here

};

#endif