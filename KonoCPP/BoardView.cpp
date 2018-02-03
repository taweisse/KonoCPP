#include "BoardView.h"

BoardView::BoardView()
{
}

BoardView::~BoardView()
{
}

void BoardView::Draw(Board boardObj) const
{
    // Define board and player colors as constants for clarity.
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

    // Set the board to the normal background colors.
    SetConsoleTextAttribute(hstdout, normColor);
    cout << 'N';
    for (int i = 0; i < boardSize; i++) {
        // Reset to normal background colors each time through the loop.
        SetConsoleTextAttribute(hstdout, normColor);
        // Output the row number.
        cout << "\n" << i + 1 << "   ";
        for (int j = 0; j < boardSize; j++) {
            // Get the occupant at the current cell.
            Piece occupant = board[i][j].occupant;
            helpers::Color occColor = occupant.GetColor();

            // Switch to board colors.
            SetConsoleTextAttribute(hstdout, boardColor);

            // Draw dashes before each cell, unless we are one the first one.
            // We dont want a dash to the left of the board.
            if (j > 0) {
                cout << "-";
            }

            if (j != 0 && !(j == boardSize - 1 && occupant.CanCapture())) {
                cout << " ";
            }

            // Pick the correct output color, depending on this cell's occupant color.
            WORD outputColor = boardColor;
            if (occColor == helpers::White) {
                outputColor = wColor;
            }
            else if (occColor == helpers::Black) {
                outputColor = bColor;
            }
            SetConsoleTextAttribute(hstdout, outputColor);

            // If the occupant can capture, we display its piece one character wider to distinguish
            // it from the rest.
            switch (occColor) {
            case helpers::White:
            case helpers::Black:
                if (occupant.CanCapture() && j == boardSize - 1) {
                    cout << ' ';
                }
                cout << (char)occColor;
                if (occupant.CanCapture() && j < boardSize - 1) {
                    cout << ' ';
                }
                break;
            default:
                cout << "+";
                if (j < boardSize - 1) {
                    cout << " ";
                }
            }

            // Set the colors back to the board colors for more output.
            SetConsoleTextAttribute(hstdout, boardColor);

            // If the occupant we just output does not have the ability to capture, we need to pad 
            // the space that it is can take up with a blank.
            if (!occupant.CanCapture() && occColor != helpers::NullColor && j < boardSize - 1) {
                cout << " ";
            }

            // End this line if we have output everything on it.
            if (j == boardSize - 1) {
                cout << "\n";
            }
        }

        if (i < boardSize - 1) {
            SetConsoleTextAttribute(hstdout, normColor);
            cout << "    ";
            SetConsoleTextAttribute(hstdout, boardColor);
            for (int i = 0; i < boardSize; i++) {
                cout << "|";
                if (i < boardSize - 1) {
                    cout << "   ";
                }   
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