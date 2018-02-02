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
    Move curMove = Play(board);
    return curMove;
}

const Move Player::Play(Board& board) 
{
    cout << "This function does nothing. It will eventually contain AI play logic. \n";
    return Move(Move::Action::Help);
}