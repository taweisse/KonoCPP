#pragma once
#include <stdexcept>
#include "Board.h"
#include "Move.h"
#include "Helpers.h"
using namespace std;

class Player
{
public:
    // Define types of player objects.
    enum PlayerType { player, human, computer };

    // We should never call this from a player object.
    Player();
    ~Player();

    // Returns the number of points that the player has accumulated.
    inline const int GetPoints() const {
        return m_points;
    }

    // Returns the color of this piece as a string.
    inline const helpers::Color GetColor() const {
        return m_color;
    }

    // Displays a menu to the player before actually making a move.
    virtual const Move PrePlay(Board&);

    // Allows the player to make a move.
    virtual const Move Play(Board&);

    // Returns the name of the player.
    virtual inline const PlayerType GetType() const {
        return player;
    }

    inline void AddPoints(int pts) {
        m_points += pts;
    }

protected:
    int m_points;
    helpers::Color m_color;

    Move BestMove(const Board&, int, int);
    Move MoveToEmptySpace(const Board&, int, int);
    Move MoveToHome(const Board&, int, int);
    Move MoveTowards(const Board&, int, int, int, int);
    Move::Direction GetDirection(int, int);

    // returns the distance between two sets of coordinates.
    int GetDistance(int curR, int curC, int tarR, int tarC) {
        return (abs(curR - tarR) + abs(curC - tarC));
    }
};