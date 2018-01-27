#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "Piece.h"
using namespace std;

class Board
{
public:
    Board(int);
    ~Board();

    // Holds information about each board location.
    struct Cell {
        char owner = 'O';
        Piece occupant = Piece();
        int value = 0;
    };

    inline const vector<vector<Cell>> GetBoardArray() const {
        return m_boardArray;
    }

    inline const int GetSize() const {
        return m_boardSize;
    }

    bool Move(const int&, const int&, const char[3], int&);

private:
    vector<vector<Cell>> m_boardArray;
    int m_boardSize;
};