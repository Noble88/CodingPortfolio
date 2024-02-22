#include "Translator.h"


Translator::Translator() { 
  cout << "Translator constructor" << endl;
  model = new Model();
}

Translator::~Translator() { 
  cout << "Translator deconstructor" << endl;
  delete model;
}

string Translator::TranslateEnglishWord(string word) {
  cout <<"DEBUG | Word = ["<< word <<"] | ";
  string translatedWord = "";
  for (int i = 0; i < word.length(); ++i) {
    char curChar = word[i];

    cout << "- curChar: " << curChar << " & is a ";
    if(std::isalpha(curChar)){ //Checks to see if valid letter of the alphabet
      
      switch(tolower(curChar)){ //To lowercase for easier easier searching
        
        case 'a': case 'e': case 'i': case 'o': case 'u': //Checks for Vowel
          cout << "[Vowel]" << endl;
          translatedWord += model->TranslateSingleVowel(word[i]); break;
        
        default: // If is a letter BUT not vowel, then MUST be constant
          cout << "[Consonant]" << endl;
          translatedWord += model->TranslateSingleConsonant(word[i]); break;
      }
    }
    else{
      cout << "[Not a letter]" << endl;
    }
  }
  cout <<"- Translation = ["<< translatedWord <<"]" <<endl;
  return translatedWord;
}

string Translator::TranslateEnglishSentence(string sentence) {
  sentence+=" ";
  string TranslatedSentence = "";
  string curWord="";
  
  for(int i = 0; i < sentence.length(); ++i){
    curWord+=sentence[i];
    if(sentence[i]==' '){
      TranslatedSentence+=TranslateEnglishWord(curWord)+" ";
      curWord="";
    }
    
  }
  return TranslatedSentence;
}