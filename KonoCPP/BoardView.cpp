#include "BoardView.h"

BoardView::BoardView()
{
}

BoardView::~BoardView()
{
}

void BoardView::DisplayBoard(vector<vector<char>> boardArr)
{
    int boardSize = boardArr[0].size();

    cout << 'N';
    for (int x = 0; x < boardSize; x++) {
        cout << "\n" << x + 1 << " ";
        for (int y = 0; y < boardSize; y++) {
            switch (boardArr[x][y]) {
            case 'W':
            case 'B':
                cout << boardArr[x][y];
                break;
            default:
                cout << '+';
            }
            
            if (y < boardSize - 1) {
                cout << " - ";
            }
            else {
                cout << "\n";
            }
        }

        if (x < boardSize - 1) {
            cout << "  ";
            for (int i = 0; i < boardSize; i++) {
                cout << "|   ";
            }
        }
    }

    cout << "S\nW ";
    for (int y = 0; y < boardSize; y++) {
        cout << y + 1;
        if (y < boardSize - 1) {
            cout << "   ";
        }
    }
    cout << " E\n";
}
