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
    static void debugMsg(const std::string& category, const std::string& fileLocation, const std::string& message);
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