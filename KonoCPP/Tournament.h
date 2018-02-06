#pragma once
#include <fstream>
#include <sstream>
#include <list>
#include "Game.h"
#include "Player.h"
using namespace std;

class Tournament
{
public:
    Tournament(Player::PlayerType = Player::player, Player::PlayerType = Player::player, Game = Game(), int = 0, int = 0, int = 0, int = 1);

    const Game GetGame() const {
        return m_currentGame;
    }

    const int GetRound() const {
        return m_roundNum;
    }

    const int GetPlayerType(int num) const {
        if (num != 1 && num != 2) {
            throw invalid_argument("There are only 2 players.");
        }
        return m_players[num - 1].m_type;
    }

    const int GetPlayerScore(int num) const {
        if (num != 1 && num != 2) {
            throw invalid_argument("There are only 2 players.");
        }
        return m_players[num - 1].m_score;
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
    string m_diceFile = "diceRolls.txt";

    int ThrowDice();
    void ConfigureGame(shared_ptr<Player>&, shared_ptr<Player>&);
};
