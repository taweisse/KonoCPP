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

    // Starts a new tournament.
    bool PlayTournament();

private:
    Game m_currentGame;
    Player m_player1;
    Player m_player2;
    int m_roundNum;

    // If this string is not empty, the code that handles throwing dice will read from the filename
    // instead of randomly choosing numbers.
    string m_diceFile = "";

    int ThrowDice();
};
