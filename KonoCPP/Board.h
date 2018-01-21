#pragma once
#include <vector>

using namespace std;

class Board
{
public:
    Board(int);
    ~Board();

    // Holds information about each board location.
    struct Cell {
        char owner;
        char occupant = 'O';
        int value;
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

