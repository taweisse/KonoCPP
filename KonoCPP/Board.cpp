#include "Board.h"

Board::Board(int size)
{
    if (size != 5 && size != 7 && size != 9) {
        throw invalid_argument("Board size invalid.");
    }
    boardSize = size;

    // Grow the board vectors to the correct size.
    boardArray.resize(boardSize);
    for (int i = 0; i < boardSize; i++) {
        boardArray[i].resize(boardSize);
    }
    // Add each players pieces to the board.
}

Board::~Board()
{
}
