#pragma once
#include "Game.h"
#include "Player.h"

class Tournament
{
public:
    Tournament();
    ~Tournament();

    const Game GetGame() const {
        return m_currentGame;
    }

    const Player GetPlayer1() const {
        return m_player1;
    }

    const Player GetPlayer2() const {
        return m_player2;
    }

    const int GetRound() const {
        return m_roundNum;
    }

    const int GetPlayer1Score() const {
        return m_player1Score;
    }

    const int GetPlayer2Score() const {
        return m_player2Score;
    }

private:
    Game m_currentGame;
    Player m_player1;
    Player m_player2;
    int m_roundNum;
    int m_player1Score;
    int m_player2Score;
};
