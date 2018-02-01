#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Move.h"

namespace helpers {
    int ShowMenu(std::string, std::vector<std::string>);
    bool ReadDigit(int&);
    bool ReadDirection(Move::Direction&);
}
