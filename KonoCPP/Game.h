#pragma once
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Human.h"
#include "Computer.h"
#include "Board.h"
#include "BoardView.h"

class Game
{
public:
    Game();
    Game(Player&, Player&, int, Board = Board());
    ~Game();

    bool PlayGame();
    
    inline const Player GetPlayer(int i) const {
        return *m_players[i - 1];
    }

    // Tests to see if this game has actually started, or if is a new object.
    inline const bool IsInitialized() const {
        // Uninitialized board objects will have size 0.
        if (m_gameboard.GetSize() == 0) {
            return false;
        }
        return true;
    }

private:
    Player* m_players[2];
    Board m_gameboard;
    BoardView m_renderer;
    int m_curPlayer;

    void PrintMove(const Move&);
    void PrintPoints();
};
