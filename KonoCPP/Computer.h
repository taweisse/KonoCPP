#pragma once
#include "Player.h"
#include "Helpers.h"

class Computer : public Player
{
public:

    Computer(helpers::Color);

    // Returns the name of the player.
    virtual const string GetTypeAsString() const {
        return "Computer";
    }

    // Displays a menu to the player before they actually make a move.
    virtual const Move PrePlay(Board&);
};

