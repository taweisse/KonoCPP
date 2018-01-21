#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class Board
{
public:
    Board(int);
    ~Board();

    // Holds information about each board location.
    struct Cell {
        char owner = 'O';
        char occupant = 'O';
        int value = 0;
    };

    inline vector<vector<Cell>> GetBoardArray() {
        return boardArray;
    }

    inline int GetSize() {
        return boardSize;
    }

private:
    vector<vector<Cell>> boardArray;
    int boardSize;
};

