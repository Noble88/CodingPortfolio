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
