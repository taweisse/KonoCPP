#pragma once
#include <string>
#include "Player.h"
#include "Helpers.h"
using namespace std;

class Human : public Player
{
public:
    Human(char);
    ~Human();

    virtual void Play(Board&);

    // Returns the name of the player.
    virtual const string GetTypeAsString() const {
        return "Human";
    }
};
