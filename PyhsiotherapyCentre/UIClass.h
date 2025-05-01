#pragma once
#include <string>
#include <iostream>
#include "Lists.h"
#include <conio.h>

class UIClass {
private:
    bool silent;

public:
    UIClass();

    std::string getFileName(const std::string& type) const;
    void printLists(Lists& lists, int timestep) const;
    void waitKeyPress() const;
    void print(const std::string& message) const;
    bool GetState();
};