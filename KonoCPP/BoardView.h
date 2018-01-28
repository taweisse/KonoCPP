#pragma once

#include <vector>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Board.h"
using namespace std;

class BoardView
{
public:
    BoardView();
    ~BoardView();

    void Draw(Board board) const;

    void DrawValues(Board board) const;

    void DrawOwner(Board board) const;
};
