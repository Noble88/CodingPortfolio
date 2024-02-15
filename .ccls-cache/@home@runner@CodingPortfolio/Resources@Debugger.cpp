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

void Debugger::debugMsg(const std::string& category, const std::string& fileLocation, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    if (enabledCategories.find(category) != enabledCategories.end()) {
        std::cout << "[DEBUG - " << fileLocation << " - " << category << "]: " << message << std::endl;
    }
}
