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
    for (int i = 0; i < boardSize; i++) {
        cout << "\n" << i + 1 << "   ";
        for (int j = 0; j < boardSize; j++) {
            switch (board[i][j].occupant) {
            case 'w':
            case 'b':
            case 'W':
            case 'B':
                cout << board[i][j].occupant;
                break;
            default:
                cout << '+';
            }
            
            if (j < boardSize - 1) {
                cout << " - ";
            }
            else {
                cout << "\n";
            }
        }

        if (i < boardSize - 1) {
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
