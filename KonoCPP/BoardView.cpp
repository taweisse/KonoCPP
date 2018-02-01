#include "BoardView.h"

BoardView::BoardView()
{
}

BoardView::~BoardView()
{
}

void BoardView::Draw(Board boardObj) const
{
    // Define board and player colors.
    const WORD normColor  = 0x07;
    const WORD boardColor = 0x87;
    const WORD wColor     = 0xF0;
    const WORD bColor     = 0x0F;

    // Set up fancy colored output.
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    SetConsoleCursorInfo(hstdout, &cursorInfo);

    // Remember default colors.
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hstdout, &csbi);

    int boardSize = boardObj.GetSize();
    vector<vector<Board::Cell>> board = boardObj.GetBoardArray();

    // Set the board to the normal backgrounf colors.
    SetConsoleTextAttribute(hstdout, normColor);
    cout << 'N';
    for (int i = 0; i < boardSize; i++) {
        SetConsoleTextAttribute(hstdout, normColor);
        cout << "\n" << i + 1 << "   ";
        for (int j = 0; j < boardSize; j++) {
            WORD outputColor = boardColor;
            Piece occupant = board[i][j].occupant;
            if (occupant.GetColor() == 'W') {
                outputColor = wColor;
            }
            else if (occupant.GetColor() == 'B') {
                outputColor = bColor;
            }

            // Set board output colors depending on the piece.
            SetConsoleTextAttribute(hstdout, outputColor);

            switch (board[i][j].occupant.GetColor()) {
            case 'W':
            case 'B':
                cout << occupant.GetColor();
                if (occupant.CanCapture()) {
                    cout << ' ';
                }
                break;
            default:
                cout << "+";
            }

            // Reset colors back to after the piece is drawn.
            SetConsoleTextAttribute(hstdout, boardColor);
            
            if (j < boardSize - 1) {
                if (!occupant.CanCapture()) {
                    cout << ' ';
                }
                cout << "- ";
            }
            else {
                cout << "\n";
            }
        }

        if (i < boardSize - 1) {
            SetConsoleTextAttribute(hstdout, normColor);
            cout << " ";
            SetConsoleTextAttribute(hstdout, boardColor);
            for (int i = 0; i < boardSize; i++) {
                cout << "   |";
            }
        }
    }

    SetConsoleTextAttribute(hstdout, normColor);
    cout << "S\n  W ";
    for (int y = 0; y < boardSize; y++) {
        cout << y + 1;
        if (y < boardSize - 1) {
            cout << "   ";
        }
    }
    cout << " E\n";

    // Set colors back to default.
    SetConsoleTextAttribute(hstdout, csbi.wAttributes);
    SetConsoleCursorInfo(hstdout, &cursorInfo);
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
