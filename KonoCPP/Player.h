#pragma once
#include <stdexcept>
#include "Board.h"
#include "Move.h"
#include "Helpers.h"
using namespace std;

class Player
{
public:
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
    virtual const string GetTypeAsString() const {
        return "Player";
    }

protected:
    int m_points;
    helpers::Color m_color;
};