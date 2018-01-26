#include "BoardView.h"

BoardView::BoardView()
{
}

BoardView::~BoardView()
{
}

void BoardView::Draw(Board boardObj) const
{
    int boardSize = boardObj.GetSize();
    vector<vector<Board::Cell>> board = boardObj.GetBoardArray();

    cout << 'N';
    for (int i = 0; i < boardSize; i++) {
        cout << "\n" << i + 1 << "   ";
        for (int j = 0; j < boardSize; j++) {
            switch (board[i][j].occupant.GetColor()) {
            case 'W':
            case 'B':
                if (board[i][j].occupant.CanCapture()) {
                    cout << (char)board[i][j].occupant.GetColor();
                }
                else {
                    cout << (char)tolower(board[i][j].occupant.GetColor());
                }
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

void BoardView::DrawValues(Board boardObj) const
{
    int boardSize = boardObj.GetSize();
    vector<vector<Board::Cell>> board = boardObj.GetBoardArray();

    cout << 'N';
    for (int i = 0; i < boardSize; i++) {
        cout << "\n" << i + 1 << "   ";
        for (int j = 0; j < boardSize; j++) {
            cout << board[i][j].value;

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

void BoardView::DrawOwner(Board boardObj) const
{
    int boardSize = boardObj.GetSize();
    vector<vector<Board::Cell>> board = boardObj.GetBoardArray();

    cout << 'N';
    for (int i = 0; i < boardSize; i++) {
        cout << "\n" << i + 1 << "   ";
        for (int j = 0; j < boardSize; j++) {
            cout << board[i][j].owner;

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
