#pragma once
#include "Game.h"
#include "Player.h"
using namespace std;

class Tournament
{
public:
    Tournament(Player::PlayerType = Player::player, Player::PlayerType = Player::player, Game = Game(), int = 0, int = 0, int = 0, int = 1);
    ~Tournament();

    const Game GetGame() const {
        return m_currentGame;
    }

    const int GetRound() const {
        return m_roundNum;
    }

    // Starts a new tournament.
    bool PlayTournament();

private:
    struct TournPlayer {
        Player::PlayerType m_type;
        int m_score;
    };

    TournPlayer m_players[2];
    Game m_currentGame;
    int m_roundNum;
    int m_firstPlayer;

    // If this string is not empty, the code that handles throwing dice will read from the filename
    // instead of randomly choosing numbers.
    string m_diceFile = "";

    int ThrowDice();
    void ConfigureGame(Player*&, Player*&);
};
