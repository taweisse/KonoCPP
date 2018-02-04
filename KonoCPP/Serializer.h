#pragma once
#include "Tournament.h"
#include "Player.h"
#include <iostream>
#include <fstream>

class Serializer
{
public:
    static bool SerializeToFile(const Tournament&, const string&);
    static bool UnserializeFromFile(const Tournament&, const string&);
};
