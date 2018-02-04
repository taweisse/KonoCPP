#pragma once
#include <string>
#include "Player.h"
#include "Helpers.h"
using namespace std;

class Human : public Player
{
public:

    Human(const helpers::Color& = helpers::NullColor, const int& = 0);

    // Displays a menu to the player before they actually make a move.
    virtual const Move PrePlay(Board&);

    // Actually make a move.
    virtual const Move Play(Board&);

    // Returns the name of the player.
    virtual inline const PlayerType GetType() const {
        return human;
    }
};
