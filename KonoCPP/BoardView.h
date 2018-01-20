#pragma once

#include <vector>
#include <iostream>
using namespace std;

class BoardView
{
public:
    BoardView();
    ~BoardView();

    void DisplayBoard(vector<vector<char>> board);
};

