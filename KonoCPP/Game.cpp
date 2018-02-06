#include "Game.h"

Game::Game()
{
    // Default constructor creates generic objects.
    m_players[0] = nullptr;
    m_players[1] = nullptr;
    m_gameboard = Board();
    m_renderer = BoardView();
    m_curPlayer = 0;
}

Game::Game(shared_ptr<Player> p1, shared_ptr<Player> p2, int curPlayer, Board board)
{
    m_players[0] = p1;
    m_players[1] = p2;
    m_gameboard = board;
    m_renderer = BoardView();
    if (curPlayer < 1 || curPlayer > 2) {
        throw invalid_argument("Invalid player number.");
    }
    m_curPlayer = curPlayer - 1;
}

// Starts a game.
bool Game::PlayGame() 
{
    // Display initial setup to the user.
    for (int i = 0; i < 2; i++) {
        cout << "Player " << i + 1 << " is ";
        char color = m_players[i]->GetColor();
        if (color == 'W') {
            cout << "white. \n";
        }
        else {
            cout << "black. \n";
        }
    }
    cout << "\n";

    // Alternate moves between the players.
    while (1) {
        cout << "Player " << m_curPlayer + 1 << "'s turn: \n\n";
        m_renderer.Draw(m_gameboard);
        cout << "\n";

        // Loop until player completes a move.
        while (1) {
            // Let the current player make a move.
            Move thisMove = m_players[m_curPlayer]->PrePlay(m_gameboard);

            // the player chose to move a piece.
            if (thisMove.GetAction() == Move::Play) {
                cout << "\nPlayer " << m_curPlayer + 1 << " executes a ";
                PrintMove(thisMove);
                cout << "\n";
                PrintPoints();
                break;
            }
            // If the player chooses to save we will return false because the game is not finished.
            else if (thisMove.GetAction() == Move::Save) {
                return false;
            }
            // If the user asked for help, we will display the move that the computer suggested.
            else if (thisMove.GetAction() == Move::Help) {
                cout << "\nThe computer suggests a ";
                PrintMove(thisMove);
                cout << "\n";
                continue;
            }
            // Return true if the player quits. This means the game is over.
            else {
                cout << "\nPlayer " << m_curPlayer + 1 << " quits the game.\n";
                return true;
            }
        }

        // After each move check if someone has won. Return true if they have, since the game is
        // completed.
        helpers::Color winner = m_gameboard.GetWinner();
        if (winner != helpers::NullColor) {
            cout << "Player " << m_curPlayer + 1 << " wins the game!\n";
            return true;
        }

        cout << "\n----------\n\n";
        
        // Switch to the next player.
        m_curPlayer = (m_curPlayer == 0) ? 1 : 0;
    }

    return true;
}

// Nicely prints a Move object.
void Game::PrintMove(const Move& move)
{
    cout << "move ";

    int r = move.GetRow();
    int c = move.GetCol();
    int rDest, cDest;
    Move::Direction dir = move.GetDir();
    if (dir == Move::NW) {
        cout << "northwest";
        rDest = r - 1;
        cDest = c - 1;
    }
    else if (dir == Move::NE) {
        cout << "northeast";
        rDest = r - 1;
        cDest = c + 1;
    }
    else if (dir == Move::SE) {
        cout << "southeast";
        rDest = r + 1;
        cDest = c + 1;
    }
    else {
        cout << "southwest";
        rDest = r + 1;
        cDest = c - 1;
    }

    // Output the reasoning behind why this move was made.
    cout << " from (" << r << ", " << c << ") to (" << rDest << ", " << cDest << ")\nto ";
    switch (move.GetReason()) {
    case Move::Advance:
        cout << "advance towards the opponent's home location";
        break;
    case Move::Capture:
        cout << "capture the opponent's piece";
        break;
    case Move::Escape:
        cout << "escape being captured by the opponent";
        break;
    }

    // If a target was provided in this move, output it as well.
    if (move.GetTargetRow() != -1 && move.GetTargetCol() != -1) {
        cout << " at (" << move.GetTargetRow() << ", " << move.GetTargetCol() << ")";
    }
    cout << ".\n";

    return;
}

void Game::PrintPoints() 
{
    for (int i = 0; i < 2; i++) {
        cout << "Player " << i + 1 << "'s score: " << m_players[i]->GetPoints() << "\n";
    }
}
