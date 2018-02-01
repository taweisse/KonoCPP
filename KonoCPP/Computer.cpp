#include "Computer.h"

Computer::Computer(char color)
{
    if (color == 'B' || color == 'W') {
        m_color = color;
    }
    else {
        throw invalid_argument("Invalid color.");
    }
    m_points = 0;
}

Computer::~Computer()
{
}
