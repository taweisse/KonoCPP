#pragma once
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <memory>
#include "Human.h"
#include "Computer.h"
#include "Board.h"
#include "BoardView.h"

class Game
{
public:
    Game();
    Game(shared_ptr<Player>, shared_ptr<Player>, int, Board = Board());

    bool PlayGame();
    
    const Player* const GetPlayer(int i) const {
        return m_players[i - 1].get();
    }

    const Board GetBoard() const {
        return m_gameboard;
    }

    // Get the player who will make the next move.
    const int GetNextPlayer() const {
        return m_curPlayer + 1;
    }

    // Tests to see if this game has actually started, or if is a new object.
    const bool IsInitialized() const {
        // Uninitialized board objects will have size 0.
        if (m_gameboard.GetSize() == 0) {
            return false;
        }
        return true;
    }

private:
    shared_ptr<Player> m_players[2];
    Board m_gameboard;
    BoardView m_renderer;
    int m_curPlayer;

    void PrintMove(const Move&);
    void PrintPoints();
};
