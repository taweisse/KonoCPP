#include "Game.h"

Game::Game()
{
    // Default constructor creates generic objects.
    m_player1 = Player();
    m_player2 = Player();
    m_gameboard = Board();
    m_renderer = BoardView();
}

Game::Game(Player p1, Player p2, int boardSize) 
{
    m_player1 = p1;
    m_player2 = p2;
    m_gameboard = Board(boardSize);
    m_renderer = BoardView();
}

Game::~Game()
{
}