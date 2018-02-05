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
    // Stores the coordinates and direction of the best move we have found so far.
    int bestRow = -1, bestCol = -1;
    Move::Direction bestDir = Move::NullDir;

    // Examine each location on the board.
    int boardSize = board.GetSize();
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {

        }
    }


    cout << "This function does nothing. It will eventually contain AI play logic. \n";
    return Move(Move::Help);
}