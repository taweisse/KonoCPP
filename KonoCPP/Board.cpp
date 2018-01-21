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

        // Set the color that we will use for this row, and its location.
        char color = 'O';
        string loc = "mid";
        if (i <= 1) {
            color = 'w';
            if (i == 0) {
                loc = "edge";
            }
        }
        else if (i >= boardSize - 2) {
            color = 'b';
            if (i == boardSize - 1) {
                loc = "edge";
            }
        }

        // Loop through each row to assign the array.
        if (color != 'O') {
            for (int j = 0; j < boardSize; j++) {
                if (loc == "edge" || j == 0 || j == boardSize - 1) {
                    boardArray[i][j].occupant = color;
                    boardArray[i][j].owner = color;

                    // Fill in the board's point values at each home location.
                    if (loc == "mid" || j == 1 || j == boardSize - 2) {
                        boardArray[i][j].value = 1;
                    }
                    else if (j == 0 || j == boardSize - 1) {
                        boardArray[i][j].value = 3;
                    }
                    else {
                        boardArray[i][j].value = ((min(j, boardSize - 1 - j) + 1) * 2) - 1;
                    }
                }
            }
        }
    }
}

Board::~Board()
{
}
