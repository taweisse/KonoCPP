#include "BoardView.h"

BoardView::BoardView()
{
}

BoardView::~BoardView()
{
}

void BoardView::Draw(Board boardObj)
{

    int boardSize = boardObj.GetSize();
    vector<vector<Board::Cell>> board = boardObj.GetBoardArray();

    cout << 'N';
    for (int x = 0; x < boardSize; x++) {
        cout << "\n" << x + 1 << "   ";
        for (int y = 0; y < boardSize; y++) {
            switch (board[x][y].occupant) {
            case 'w':
            case 'b':
            case 'W':
            case 'B':
                cout << board[x][y].occupant;
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
                cout << "  | ";
            }
        }
    }

    cout << "S\n  W ";
    for (int y = 0; y < boardSize; y++) {
        cout << y + 1;
        if (y < boardSize - 1) {
            cout << "   ";
        }
    }
    cout << " E\n";
}
