#ifndef MODEL_H
#define MODEL_H

#include <iostream>
using namespace std; //IF USING STRING

class Model{
  public:
    Model();  //Constructor  
    ~Model(); //Deconstructor

/*Purpose: returns a string representing its encoding in Rövarspråket. Capitalization should be preserved.*/
  string TranslateSingleConsonant(char const);


/*Purpose: takes a single vowel character, returns a string representing its encoding in Rövarspråket. Capitalization should be preserved.*/
  string TranslateSingleVowel(char const);

/*Purpose of Model Class...
-Use method to turn a vowel or consitenant and give the translation of it 
-Rövarspråket encoding: Every consonant (spelling matters, not pronunciation) is doubled, and an o is inserted in between. Vowels are left intact.
*/
};



#endif