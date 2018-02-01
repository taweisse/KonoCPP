#pragma once
#include "Tournament.h"
#include <iostream>
#include <fstream>

class Serializer
{
public:
    Serializer();
    ~Serializer();

    int SerializeToFile(const Tournament&, const string&);
    int UnserializeFromFile(const Tournament&, const string&);
};
