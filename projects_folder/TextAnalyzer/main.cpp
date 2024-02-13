#include "TextAnalyzer.h"
#include <iostream>

int main() {
  TextAnalyzer textAnalyzer;
  std::cout << "Analizing vowel count from the sentence: \"How many vowels are in this sentence?\"\n";
  std::string sentence = "How many vowels are in this sentence?";
  int vowelCount = textAnalyzer.countVowels(sentence);
  std::cout << "The sentence has " << vowelCount << " vowels." << std::endl;
  return 0;
}