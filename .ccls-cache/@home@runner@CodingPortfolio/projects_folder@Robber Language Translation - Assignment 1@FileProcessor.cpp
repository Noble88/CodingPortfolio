#include "FileProcessor.h"

FileProcessor::FileProcessor(){
  cout << "FileProcessor constructor" << endl;
}

FileProcessor::~FileProcessor(){
  cout << "FileProcessor deconstructor" << endl;
}


void FileProcessor::ProcessFile(string inputFileName, string outputFileName){
  ifstream input(inputFileName); // Open input file for reading
  ofstream output(outputFileName); // Open output file for writing
  
  //Check if files are open
  if (!input.is_open() || !output.is_open()) {
      cerr << "Error opening files!" << endl;
      return;
  }

  // Start HTML file
  output << "<html><body>" << endl;

  Translator translator; // Assuming you have a Translator class ready to use
  string line;

  while (getline(input, line)) { // Read each line from the input file
      string translatedLine = translator.TranslateEnglishSentence(line); // Translate the line

      // Write original and translated lines to the HTML file
      output << "<b>" << line << "</b><br><i>" << translatedLine << "</i><br><br>" << endl;
  }

  // End HTML file
  output << "</body></html>" << endl;

  // Close the files
  input.close();
  output.close();
  
}
