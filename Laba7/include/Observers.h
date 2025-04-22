
#pragma once

#include <string>
#include <cmath>
#include <fstream>


class Observer {
public:
    virtual void update(const std::string& event) = 0;
    virtual ~Observer() = default;
};

class ScreenObserver : public Observer {
public:
    void update(const std::string& event) override;
};

class FileObserver : public Observer {
private:
    std::ofstream logFile;
public:
    FileObserver(const std::string& filename);
    void update(const std::string& event) override;
    ~FileObserver();
};