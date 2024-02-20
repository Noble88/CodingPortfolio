#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <iostream>
#include "../Model.h"

using namespace std; //IF USING STRING

class Translator{
private:
  Model model;

  public:
    Translator();  // Constructor    
    ~Translator(); // Deconstructor

    string TranslateEnglishWord(string word);
/*Purpose: takes a single string representing a single English word as input
and returns a string representing the Rövarspråket translation.*/

    string TranslateEnglishSentence(string sentence);
/*Purpose: takes a single string representing a single English sentence
as input and returns a string representing the Rövarspråket translation. Make sure to account for punctuation*/
};

#endif
