#include <cstdlib>
#include <iostream>
#include <string>
#include "TerminalManager/TerminalHandler.h"

#include "Resources/Debugger/Debugger.h"

int main() {
  Debugger::enableCategory("Main Method");
  Debugger::enableCategory("TERMINNAL_HANDLER");
  ///DEBUG_MSG("RUNNING PROJECT MANAGER MAIN\n");

  TerminalHandler terminalHandler;
  terminalHandler.Run();
  return 0;
}

/*TODO: 
- MEGA IMPORTANT: Make it so ignore projects with bad code so doesn't break when run 
-MEGA IMPROTSNT: see if run button actually works!!!!!!!
- make it so can upload changes to github and also rebuild files. Question: will building an executable while using executable break something? If so make a command so only builds projects in projects folder
- Add debugger think that every class can use
*/

//Questions to ask: When make a read me 
