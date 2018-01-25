#include "Board.h"

// Constructor. Set up the board for a new game.
Board::Board(int size, Player &white, Player &black) 
    : m_whitePlayer(white), m_blackPlayer(black)
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
        if (color == 'O') {
            continue;
        }
        for (int j = 0; j < m_boardSize; j++) {
            if (loc == "edge" || j == 0 || j == m_boardSize - 1) {
                m_boardArray[i][j].occupant = color;
                m_boardArray[i][j].owner = toupper(color);

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

// Moves a player's piece on the board. Returns -1 if the move was unsuccessful. This function
// takes 0 - indexed coordinates.
int Board::Move(Player& player, const int& vertPos, const int& horPos, const string& dir)
{
    // Make sure the player is moving his own piece.
    char playerColor = player.GetColor();
    Cell& moveCell = m_boardArray[vertPos][horPos];

    // Opponent's color is opposite the player who is moving.
    char oppColor;
    switch (playerColor) {
    case 'W':
        oppColor = 'B';
        break;
    case 'B':
        oppColor = 'W';
        break;
    }

    // Make sure the player is moving his piece.
    if (toupper(moveCell.occupant) == oppColor) {
        cout << "You cannot move another player's piece. \n";
        return -1;
    }
    else if (moveCell.occupant == 'O') {
        cout << "There is no piece at the given location. \n";
        return -1;
    }
    
    // Determine where the player wants to move.
    int targetVertPos, targetHorPos;
    if (dir == "NW") {
        targetVertPos = vertPos - 1;
        targetHorPos = horPos - 1;
    }
    else if (dir == "NE") {
        targetVertPos = vertPos - 1;
        targetHorPos = horPos + 1;
    }
    else if (dir == "SE") {
        targetVertPos = vertPos + 1;
        targetHorPos = horPos + 1;
    }
    else if (dir == "SW") {
        targetVertPos = vertPos + 1;
        targetHorPos = horPos - 1;
    }
    else {
        throw invalid_argument("Invalid move direction.");
        return -1;
    }

    // Validate the user's move direction. It must stay within bounds.
    if (targetVertPos >= m_boardSize || targetVertPos < 0 || targetHorPos >= m_boardSize || targetHorPos < 0) {
        cout << "Invalid move direction. A move must remain within the board's bounds. \n";
        return -1;
    }

    // Validate that the player can move to the desired location. It must be empty, or the piece 
    // must have the ability to capture.
    Cell& targetCell = m_boardArray[targetVertPos][targetHorPos];
    if (toupper(targetCell.occupant) == playerColor) {
        cout << "You cannot capture your own piece. \n";
        return -1;
    }
    else if (toupper(targetCell.occupant) == oppColor && islower(moveCell.occupant)) {
        cout << "This piece does not have the abililty to capture. \n";
        return -1;
    }

    // We are allowed to execute the move if we have made it this far.
    if (targetCell.owner == oppColor || moveCell.owner == oppColor) {
        player.AddPoints(targetCell.value - moveCell.value);
    }
    if (toupper(targetCell.occupant) == oppColor) {
        player.AddPoints(5);
    }
    targetCell = moveCell;
    moveCell.occupant = 'O';
}
