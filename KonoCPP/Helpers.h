#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Move.h"

namespace helpers {

    // Define player colors.
    enum Color { White = 87, Black = 66, NullColor = 79 };

    int ShowMenu(std::string, std::vector<std::string>);
    bool ReadDigit(int&);
    bool ReadDirection(Move::Direction&);
}
