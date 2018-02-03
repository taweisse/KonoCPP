#include "Human.h"

Human::Human(const helpers::Color color)
{
    m_color = color;
    m_points = 0;
}

const Move Human::PrePlay(Board& board)
{
    Move thisMove;
    int choice = helpers::ShowMenu("Please select an option:", { "Save & Exit", "Make a Move", "Ask For Help", "Quit Game" });
    switch (choice) {
    case 1:
        thisMove = Move(Move::Save);
        break;
    case 2:
        thisMove = Play(board);
        break;
    case 3:
        thisMove = Player::Play(board);
        break;
    default:
        thisMove = Move(Move::Quit);
        m_points -= 5;
        break;
    }

    // Return the move that we just played.
    return thisMove;
}

const Move Human::Play(Board& board) 
{
    int row, col;
    Move::Direction dir;
    Move thisMove;

    // Loop while input is invalid. Break once user inputs a valid move.
    while (1) {
        // Get coordinates of the move.
        while (1) {
            cout << "\nEnter Row: \n";
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
            cout << "Direction invalid. \n";
        }
        // Build and perform the move. The function will return true if successful, in which case we 
        // can break from the loop and complete this player's turn.
        int pts = 0;
        thisMove = Move(row, col, dir, Move::Play, Move::Null);
        if (!board.MakeMove(thisMove, pts)) {
            continue;
        }
        // If we make it here, the move was successful, so we can add the points recieved to the 
        // player's score.
        m_points += pts;
        break;
    }
    return thisMove;
}