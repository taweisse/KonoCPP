#pragma once
#include "Player.h"

class Computer : public Player
{
public:
    Computer(char color);
    ~Computer();

    // Returns the name of the player.
    virtual const string GetTypeAsString() const {
        return "Computer";
    }
};

