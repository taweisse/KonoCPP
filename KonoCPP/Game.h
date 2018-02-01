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
    Game(Player, Player, int);
    ~Game();

private:
    Player m_player1;
    Player m_player2;
    Board m_gameboard;
    BoardView m_renderer;
};
