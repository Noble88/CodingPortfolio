#include <cstdlib>
#include <iostream>
#include <string>
#include "TerminalManager/TerminalHandler.h"

int main() {
  std::cout << "RUNNING PROJECT MANAGER MAIN" << std::endl;
  TerminalHandler terminalHandler;
  terminalHandler.Run();
  return 0;
}

/*TODO: 
- make it so can upload changes to github and also rebuild files. Question: will building an executable while using executable break something? If so make a command so only builds projects in projects folder
- Add debugger think that every class can use
*/

//Questions to ask: When make a read me 
