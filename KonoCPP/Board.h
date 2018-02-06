#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <string>
#include "Piece.h"
#include "Move.h"
#include "Helpers.h"
using namespace std;

class Board
{
public:

    enum MoveError { Null = 0, Empty = 1, Direction = 2, Occupied = 3, Capture = 4 };

    // Default constructor will create a 0 - sized board.
    Board()
    {
        m_boardArray.resize(0);
        m_boardSize = 0;
    }

    Board(int);

    // Constructs a board object based on a vector of serialization data.
    Board(vector<string>, int&, int&);

    inline const int GetSize() const {
        return m_boardSize;
    }

    MoveError MakeMove(const Move&, int&);

    const char GetOccupantColor(const int& row, const int& col) const;

    const helpers::Color GetOwner(int r, int c) const {
        if (r < 1 || r > m_boardSize || c < 1 || c > m_boardSize) {
            throw invalid_argument("you are off the board.");
        }
        return m_boardArray[r - 1][c - 1].owner;
    }

    const Piece GetOccupant(int r, int c) const {
        if (r < 1 || r > m_boardSize || c < 1 || c > m_boardSize) {
            throw invalid_argument("you are off the board.");
        }
        return m_boardArray[r - 1][c - 1].occupant;
    }

    const int GetValue(int r, int c) const {
        if (r < 1 || r > m_boardSize || c < 1 || c > m_boardSize) {
            throw invalid_argument("you are off the board.");
        }
        return m_boardArray[r - 1][c - 1].value;
    }

    // Determines if there is a winner for this game. Returns NullColor if not.
    helpers::Color GetWinner();

private:
    // Holds information about each board location.
    struct Cell {
        helpers::Color owner = helpers::NullColor;
        Piece occupant = Piece();
        int value = 0;
    };

    vector<vector<Cell>> m_boardArray;
    int m_boardSize;
    
    // Initializes the board with default values depending on the size.
    void InitializeBoard(int);
};