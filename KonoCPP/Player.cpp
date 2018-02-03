#include "Player.h"

Player::Player()
{
    m_color = helpers::NullColor;
    m_points = 0;
}

Player::~Player()
{
}

const Move Player::PrePlay(Board& board) 
{
    return Play(board);
}

const Move Player::Play(Board& board) 
{
    cout << "This function does nothing. It will eventually contain AI play logic. \n";
    return Move(Move::Help);
}