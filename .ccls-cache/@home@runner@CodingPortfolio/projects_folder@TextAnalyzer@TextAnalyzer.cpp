#include "TextAnalyzer.h"

TextAnalyzer::TextAnalyzer(){
  cout << "constructor" << endl;
}

TextAnalyzer::~TextAnalyzer(){
  cout << "deconstructor" << endl;
}

int TextAnalyzer::countVowels(std::string strContent){
  int vowelCount = 0;
  for (size_t i = 0; i < strContent.length(); ++i) {
    switch(std::tolower(strContent[i])){
      case 'a': case 'e': case 'i': case 'o': case 'u':
        vowelCount++;break;
    }
  }
  return vowelCount;
}