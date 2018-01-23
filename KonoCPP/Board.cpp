#include "Board.h"

Board::Board(int size)
{
    if (size != 5 && size != 7 && size != 9) {
        throw invalid_argument("Board size invalid.");
    }
    m_boardSize = size;

    // Grow the board vectors to the correct size.
    m_boardArray.resize(m_boardSize);
    for (int i = 0; i < m_boardSize; i++) {
        m_boardArray[i].resize(m_boardSize);

        // Set the color that we will use for this row, and its location.
        char color = 'O';
        string loc = "mid";
        if (i <= 1) {
            color = 'w';
            if (i == 0) {
                loc = "edge";
            }
        }
        else if (i >= m_boardSize - 2) {
            color = 'b';
            if (i == m_boardSize - 1) {
                loc = "edge";
            }
        }

        // Loop through each row to assign the array.
        if (color != 'O') {
            for (int j = 0; j < m_boardSize; j++) {
                if (loc == "edge" || j == 0 || j == m_boardSize - 1) {
                    m_boardArray[i][j].occupant = color;
                    m_boardArray[i][j].owner = color;

                    // Fill in the board's point values at each home location.
                    if (loc == "mid" || j == 1 || j == m_boardSize - 2) {
                        m_boardArray[i][j].value = 1;
                    }
                    else if (j == 0 || j == m_boardSize - 1) {
                        m_boardArray[i][j].value = 3;
                    }
                    else {
                        m_boardArray[i][j].value = ((min(j, m_boardSize - 1 - j) + 1) * 2) - 1;
                    }
                }
            }
        }
    }
}

Board::~Board()
{
}

int Board::Move(char color, int xPos, int yPos, string dir)
{
    return 0;
}
