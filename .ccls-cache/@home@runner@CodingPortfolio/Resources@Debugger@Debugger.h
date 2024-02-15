#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include <unordered_set>
#include <string>
#include <mutex>

class Debugger {
private:
    static std::unordered_set<std::string> enabledCategories;
    static std::mutex mutex;

public:
    static void enableCategory(const std::string& category);
    static void disableCategory(const std::string& category);

    static void debugMsg(const std::string& fileLocation, const std::string& message); // Make it public
    static void DebugMethod(const std::string& fileLocation, const std::string& methodName, const std::string& message);

    // Macro to simplify debug messages
#define DEBUG_MSG(message) Debugger::debugMsg(__FILE__, message)
#define DEBUG_METHOD(methodName, message) Debugger::DebugMethod(__FILE__, methodName, message)
};

#endif // DEBUGGER_H








/*
Debugging method

void DebugFormatting(std::string methodName, std::string debugMessage){//GEneric Method
  if(debugCode){
    std::cout << "DEBUG | Method: "+methodName+" | Message: "+debugMessage << std::endl;
  }
}
void DebugFormatting(std::string methodName, std::string testingVar, std::string description){//Testing for Variables
  if(debugCode){
    std::cout << "DEBUG | Method: "+methodName+" | Var: "+testingVar+" | Message: "+description << std::endl;
  }
}
*/