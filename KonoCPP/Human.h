#pragma once
#include "Player.h"

bool ReadDigit(int&);
bool ReadDirection(char[3]);

class Human : public Player
{
public:
    Human();
    ~Human();

    virtual void Play(Board&);
};

