#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "Player.h"
using namespace std;

class Board
{
public:
    Board(int, Player &, Player &);
    ~Board();

    // Holds information about each board location.
    struct Cell {
        char owner = 'O';
        char occupant = 'O';
        int value = 0;
    };

    inline const vector<vector<Cell>> GetBoardArray() const {
        return m_boardArray;
    }

    inline const int GetSize() const {
        return m_boardSize;
    }

    int Move(Player&, const int&, const int&, const string&);

private:
    vector<vector<Cell>> m_boardArray;
    int m_boardSize;

    // References to the player objects playing on this board.
    Player& m_whitePlayer;
    Player& m_blackPlayer;
};