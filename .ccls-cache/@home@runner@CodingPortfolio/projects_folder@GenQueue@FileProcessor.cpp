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

  // Write the HTML boilerplate and header
  output << "<!DOCTYPE html>\n<html>\n<head>\n<title>English to Robber Translation</title>\n</head>\n<body>\n";
  
  // First pass: Write all the English lines
  string line;
  while (getline(input, line)) {
      output << "<p><b>" << line << "</b><br></p>\n";
  }

  // Close and reopen the input file for the second pass
  input.close();
  input.open(inputFileName);

  //Add space as instructed
  output<<"<p><b></b><br></p>\n";
  Translator translator; // Assuming you have a Translator class ready to use

  // Second pass: Append all the translated lines
  while (getline(input, line)) {
      string translatedLine = translator.TranslateEnglishSentence(line); // Translate the line
      output << "<p><i>" << translatedLine << " </i><br></p>\n";
  }

  // Close the HTML document
  output << "</body>\n</html>";

  // Close the files
  input.close();
  output.close();
  
}
