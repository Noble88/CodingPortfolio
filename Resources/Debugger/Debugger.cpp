#include "Debugger.h"

std::unordered_set<std::string> Debugger::enabledCategories;
std::mutex Debugger::mutex;

void Debugger::enableCategory(const std::string& category) {
    std::lock_guard<std::mutex> lock(mutex);
    enabledCategories.insert(category);
}

void Debugger::disableCategory(const std::string& category) {
    std::lock_guard<std::mutex> lock(mutex);
    enabledCategories.erase(category);
}

void Debugger::debugMsg(const std::string& fileLocation, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    if (enabledCategories.empty()) {
        return; // No categories enabled, do not print debug message
    }

    // Construct debug message with file location and message
    std::string debugMessage = "DEBUGGER: In File: \"" + fileLocation + "\" | Message" + message;

    // Print debug message
    std::cout << debugMessage << std::endl;
}

void Debugger::DebugMethod(const std::string& fileLocation, const std::string& methodName, const std::string& message){
    std::lock_guard<std::mutex> lock(mutex);
    if (enabledCategories.empty()) {
        return; // No categories enabled, do not print debug message
    }

    // Construct debug message with file location and message
    std::string debugMessage = "DEBUGGER: In File: \"" + fileLocation + "\" | Method: "+methodName+" | Message: " + message;

    // Print debug message
    std::cout << debugMessage << std::endl;
}
