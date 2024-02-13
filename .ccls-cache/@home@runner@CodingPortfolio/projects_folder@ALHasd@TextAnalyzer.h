#ifndef TEXTANALYZER_H
#define TEXTANALYZER_H

#include <iostream> // pre-processor directive, system defined header
using namespace std;

class TextAnalyzer{

    public:
        TextAnalyzer(); //constructor
        ~TextAnalyzer(); //destructor
        int countVowels(string userInput);

    private:
        //private class members go here
};
#endif