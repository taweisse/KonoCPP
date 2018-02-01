#pragma once
#include <stdexcept>
#include "Board.h"
using namespace std;

class Player
{
public:
    // We should never call this from a player object.
    Player() {
        m_points = 0;
        m_color = 'O';
    }

    ~Player();

    // Returns the number of points that the player has accumulated.
    inline const int GetPoints() const {
        return m_points;
    }

    // Allows the player to make a move.
    virtual void Play(Board&);

    // Returns the name of the player.
    virtual const string GetTypeAsString() const {
        return "Player";
    }

protected:
    int m_points;
    int m_color;
};