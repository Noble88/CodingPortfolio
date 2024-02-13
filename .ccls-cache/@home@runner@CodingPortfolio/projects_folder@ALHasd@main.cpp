#include "TextAnalyzer.h" // user-defined header file

int main(int argc, char **argv){

    if(argc < 2){
        cerr << "invalid parameter count" << endl;
        return -1;
    }

    TextAnalyzer ta; // stack, short-term/temp storage
    TextAnalyzer *ta2 = new TextAnalyzer(); // heap, long-term storage until garbage collected

    cout << "ARGC: " << argc << endl;
    cout << "ARGV: " << argv[1] << endl;

    cout << "VOWEL COUNT: " << ta.countVowels(argv[1]) << endl;
    cout << "VOWEL COUNT: " << ta2->countVowels(argv[1]) << endl;

    delete ta2; //garbage collect
    return 0;
}