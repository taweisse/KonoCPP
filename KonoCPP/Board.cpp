#include "Board.h"

// Constructor. Set up the board for a new game.
Board::Board(int size) 
{
    // Sanity Check.
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
            color = 'W';
            if (i == 0) {
                loc = "edge";
            }
        }
        else if (i >= m_boardSize - 2) {
            color = 'B';
            if (i == m_boardSize - 1) {
                loc = "edge";
            }
        }

        // Loop through each row to assign the array.
        if (color == 'O') {
            continue;
        }
        for (int j = 0; j < m_boardSize; j++) {
            if (loc == "edge" || j == 0 || j == m_boardSize - 1) {
                m_boardArray[i][j].occupant = Piece(color);
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

Board::~Board()
{
}

// Moves a player's piece on the board. Returns -1 if the move was unsuccessful. Returns the number
// of points gained or lost from this move, or -1 if the move was not successful. This function 
// accepts 1 - indexed coordinates.
bool Board::Move(const int& y, const int& x, const char dir[3], int& points)
{
    int vertPos = y - 1;
    int horPos = x - 1;
    points = 0;

    Cell& moveCell = m_boardArray[vertPos][horPos];
    char moveCol = moveCell.occupant.GetColor();

    // Check that there is a piece at this location.
    if (moveCell.occupant.IsEmpty()) {
        cout << "There is no piece at the specified location.\n";
        return false;
    }

    // Make sure board coordinates are on the board.
    if (vertPos < 0 || vertPos >= m_boardSize || horPos < 0 || horPos >= m_boardSize) {
        throw invalid_argument("Move location specified is not on the board.");
    }

    // Determine where the player wants to move.
    int targetVertPos, targetHorPos;
    if (strcmp(dir, "NW") == 0) {
        targetVertPos = vertPos - 1;
        targetHorPos = horPos - 1;
    }
    else if (strcmp(dir, "NE") == 0) {
        targetVertPos = vertPos - 1;
        targetHorPos = horPos + 1;
    }
    else if (strcmp(dir, "SE") == 0) {
        targetVertPos = vertPos + 1;
        targetHorPos = horPos + 1;
    }
    else if (strcmp(dir, "SW") == 0) {
        targetVertPos = vertPos + 1;
        targetHorPos = horPos - 1;
    }
    else {
        throw invalid_argument("Invalid move direction.");
    }

    // Validate the user's move direction. It must stay within bounds.
    if (targetVertPos >= m_boardSize || targetVertPos < 0 || targetHorPos >= m_boardSize || targetHorPos < 0) {
        cout << "Invalid move direction. A move must remain within the board's bounds. \n";
        return false;
    }

    Cell& targetCell = m_boardArray[targetVertPos][targetHorPos];
    char targetCol = targetCell.occupant.GetColor();

    // Validate that the player can move to the desired location. It must be empty, or the piece 
    // must have the ability to capture.
    if (!targetCell.occupant.IsEmpty()) {
        if (moveCol == targetCol) {
            cout << "You already have a piece at this location. \n";
            return false;
        }
        // This means the opponent occupies the target cell.
        else if (!moveCell.occupant.CanCapture()) {
            cout << "This piece does not have the abililty to capture. \n";
            return false;
        }
    }

    // We are allowed to execute the move if we have made it this far.
    // First, calculate the points to be added to the player's score from this move.
    if ((moveCol != targetCell.owner && targetCell.owner != 'O') || (moveCol != moveCell.owner && moveCell.owner != 'O')) {
        points += (targetCell.value - moveCell.value);
    }

    if (!targetCell.occupant.IsEmpty() && targetCol != moveCol) {
        points += 5;
    }

    // Allow the piece to capture if we reach the opponent's home location.
    if (targetCell.owner != 'O' && moveCol != targetCell.owner) {
        moveCell.occupant.AllowCapture();
    }

    // Perform the move.
    targetCell.occupant = moveCell.occupant;
    moveCell.occupant = Piece();

    return true;
}
