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
        return m_boardArray;
    }

    inline int GetSize() {
        return m_boardSize;
    }

    int Move(char color, int xPos, int yPos, string dir);

private:
    vector<vector<Cell>> m_boardArray;
    int m_boardSize;
};