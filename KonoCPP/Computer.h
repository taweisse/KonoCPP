#pragma once
#include "Player.h"
#include "Helpers.h"

class Computer : public Player
{
public:

    Computer(const helpers::Color& = helpers::NullColor, const int& = 0);

    // Returns the name of the player.
    virtual const PlayerType GetType() const {
        return computer;
    }

    // Displays a menu to the player before they actually make a move.
    virtual const Move PrePlay(Board&);
};

