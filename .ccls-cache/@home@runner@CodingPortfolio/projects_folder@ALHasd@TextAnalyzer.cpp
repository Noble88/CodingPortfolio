#include "TextAnalyzer.h" // user-defined header

TextAnalyzer::TextAnalyzer(){
    cout << "constructor" << endl;
}

TextAnalyzer::~TextAnalyzer(){
    cout << "destructor" << endl;
}

int TextAnalyzer::countVowels(string userInput){

    int count = 0;

    for(int i = 0; i < userInput.size(); ++i){

        if(tolower(userInput[i]) == 'a')
            count++;
        else if(tolower(userInput[i]) == 'e')
            count++;
        else if(tolower(userInput[i]) == 'i')
            count++;
        else if(tolower(userInput[i]) == 'o')
            count++;
        else if(tolower(userInput[i]) == 'u')
            count++;
    }
    return count;
}