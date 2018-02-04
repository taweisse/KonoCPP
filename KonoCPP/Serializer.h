#pragma once
#include "Tournament.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>

class Serializer
{
public:
    static bool SerializeToFile(const Tournament&, const string&);
    static bool UnserializeFromFile(Tournament&, const string&);

private:
    static void LoadPlayerData(ifstream&, int&, helpers::Color&);
    static void LoadBoardData(ifstream&, vector<string>&);
};
