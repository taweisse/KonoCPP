#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace helpers {
    int ShowMenu(std::string, std::vector<std::string>);
    bool ReadDigit(int&);
    bool ReadDirection(char[3]);
}
