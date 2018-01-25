#include "Player.h"

Player::Player(char color)
{
    if (color != 'B' && color != 'W') {
        throw invalid_argument("Player color invalid.");
    }
    m_color = color;
}

Player::~Player()
{
}
