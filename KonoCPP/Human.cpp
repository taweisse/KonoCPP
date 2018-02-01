#include "Human.h"

Human::Human(char color)
{
    if (color == 'B' || color == 'W') {
        m_color = color;
    }
    else {
        throw invalid_argument("Color invalid.");
    }
    m_points = 0;
}

Human::~Human()
{
}

void Human::Play(Board& board) 
{
    int row, col;
    char dir[3];

    // Loop while input is invalid. Break once user inputs a valid move.
    while (1) {
        // Get coordinates of the move.
        while (1) {
            cout << "Enter Row: \n";
            if (helpers::ReadDigit(row) && row > 0 && row <= board.GetSize()) {
                break;
            }
            cout << "Entry invalid. ";
        }
        while (1) {
            cout << "Enter Column: \n";
            if (helpers::ReadDigit(col) && col > 0 && col <= board.GetSize()) {
                break;
            }
            cout << "Entry invalid. ";
        }
        // Validate that the location entered is the right color. If the location given is not on
        // the board, catch the exception and let the user know.
        try {
            char pieceColor = board.GetOccupantColor(row, col);
            if (pieceColor != m_color && pieceColor != 'O') {
                cout << "You can only move your own piece. \n";
                continue;
            }
            else if (pieceColor == 'O') {
                cout << "There is no piece in that location. \n";
                continue;
            }
        }
        catch (invalid_argument) {
            cout << "That location is not on the board. \n";
            continue;
        }

        // Get direction of the move.
        while (1) {
            cout << "Enter move direction: ( NW, NE, SE, SW ) \n";
            if (helpers::ReadDirection(dir)) {
                break;
            }
            cout << "Direction invalid. ";
        }
        // Perform the move. The function will return true if successful, in which case we can break
        // from the loop and complete this player's turn.
        int pts = 0;
        if (!board.Move(row, col, dir, pts)) {
            continue;
        }
        // If we make it here, the move was successful, so we can add the points recieved to the 
        // player's score.
        m_points = pts;
        break;
    }
}