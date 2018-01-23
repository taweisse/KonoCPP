#pragma once
#include <stdexcept>
using namespace std;

class Player
{
public:
    Player(char color);
    ~Player();

private:
    char m_color = 'O';
    int m_points = 0;
};