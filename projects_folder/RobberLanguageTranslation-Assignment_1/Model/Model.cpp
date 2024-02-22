#include "Model.h"

Model::Model(){ cout << "Model Constructor" << endl; }
Model::~Model(){ cout << "Model Deconstructor" << endl; }

string Model::TranslateSingleConsonant(char consonant){
  return string(1, consonant)+"o"+string(1, consonant);
}

string Model::TranslateSingleVowel(char vowel){
  return string(1,vowel);
}
