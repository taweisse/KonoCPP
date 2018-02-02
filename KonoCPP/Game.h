#pragma once
#include <vector>
#include <string>
#include "Human.h"
#include "Computer.h"
#include "Board.h"
#include "BoardView.h"

class Game
{
public:
    Game();
    Game(Player&, Player&, int);
    ~Game();

    bool PlayGame();

private:
    Player* m_players[2];
    Board m_gameboard;
    BoardView m_renderer;

    void PrintMove(const Move&);
};
