#include "../include/Observers.hpp"
#include <fstream>
#include <iostream>


void ScreenObserver::update(const std::string& event) {
    std::cout << event << std::endl;
}

FileObserver::FileObserver(const std::string& filename) {
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error opening log file.\n";
    }
}

void FileObserver::update(const std::string& event) {
    if (logFile.is_open()) {
        logFile << event << std::endl;
    } else {
        std::cerr << "Log file is not open for writing.\n";
    }
}

FileObserver::~FileObserver() {
    if (logFile.is_open()) {
        logFile.close();
    }
}