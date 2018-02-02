#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "Piece.h"
#include "Move.h"
#include "Helpers.h"
using namespace std;

class Board
{
public:
    // Default constructor will create a 0 - sized board.
    Board()
    {
        m_boardArray.resize(0);
        m_boardSize = 0;
    }

    Board(int);
    ~Board();

    // Holds information about each board location.
    struct Cell {
        helpers::Color owner = helpers::NullColor;
        Piece occupant = Piece();
        int value = 0;
    };

    inline const vector<vector<Cell>> GetBoardArray() const {
        return m_boardArray;
    }

    inline const int GetSize() const {
        return m_boardSize;
    }

    bool MakeMove(const Move&, int&);

    inline const char GetOccupantColor(const int& row, const int& col) const {
        int r = row - 1;
        int c = col - 1;
        if (r >= 0 && r < m_boardSize && c >= 0 && c < m_boardSize) {
            return m_boardArray[r][c].occupant.GetColor();
        }
        throw invalid_argument("Row or column out of board range.");
    }

    // Determines if there is a winner for this game. Returns NullColor if not.
    helpers::Color GetWinner();

private:
    vector<vector<Cell>> m_boardArray;
    int m_boardSize;
};