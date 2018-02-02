#include "Game.h"

Game::Game()
{
    // Default constructor creates generic objects.
    m_players[0] = &Player();
    m_players[1] = &Player();
    m_gameboard = Board();
    m_renderer = BoardView();
}

Game::Game(Player& p1, Player &p2, int boardSize) 
{
    m_players[0] = &p1;
    m_players[1] = &p2;
    m_gameboard = Board(boardSize);
    m_renderer = BoardView();
}

Game::~Game()
{
}


// Starts a game.
bool Game::PlayGame() {
    // Display initial setup to the user.
    for (int i = 0; i < 2; i++) {
        cout << "Player " << i + 1 << " is a ";
        char color = m_players[i]->GetColor();
        if (color == 'W') {
            cout << "white ";
        }
        else {
            cout << "black ";
        }
        cout << m_players[i]->GetTypeAsString() << "\n";
    }
    cout << "\n";

    // Alternate moves between the players.
    while (1) {
        for (int i = 0; i < 2; i++) {
            cout << "Player " << i + 1 << "'s turn: \n";
            m_renderer.Draw(m_gameboard);
            cout << "\n";
            Move thisMove = m_players[i]->PrePlay(m_gameboard);
            cout << "\nPlayer " << i + 1 << " ";
            PrintMove(thisMove);

            helpers::Color winner = m_gameboard.GetWinner();
            if (winner != helpers::NullColor) {
                cout << "YOU WIN!\n";
            }

            cout << "\n----------\n\n";
        }
    }

    return true;
}

// Nicely prints a Move object.
void Game::PrintMove(const Move& move)
{
    cout << "moves ";

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


    cout << " from (" << r << ", " << c << ") to (" << rDest << ", " << cDest << ").\n";
    return;
}