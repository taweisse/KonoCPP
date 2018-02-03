#pragma once
#include "Player.h"
#include "Helpers.h"

class Computer : public Player
{
public:

    Computer(helpers::Color = helpers::NullColor);

    // Returns the name of the player.
    virtual inline const PlayerType GetType() const {
        return computer;
    }

    // Displays a menu to the player before they actually make a move.
    virtual const Move PrePlay(Board&);
};

