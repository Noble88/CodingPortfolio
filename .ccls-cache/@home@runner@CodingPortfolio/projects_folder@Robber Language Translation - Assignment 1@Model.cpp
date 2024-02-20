#include "Model.h"

Model::Model(){
  cout << "Model constructor" << endl;
}

Model::~Model(){
  cout << "Model deconstructor" << endl;
}

/*Rövarspråket encoding: Every consonant (spelling matters, not pronunciation) is doubled, and an o is inserted in between. Vowels are left intact.
example: “stubborn” = sostotubobboborornon
*/
string Model::TranslateSingleConsonant(char consonant){
  string translation = to_string(consonant+'o'+consonant);
  
  cout << "Model Class/TranslateSingleConsonant output = [" <<translation<<"]"; //DEBUGGING
  
  return translation;
  
}

string Model::TranslateSingleVowel(char vowel){
  return to_string(vowel);
}
