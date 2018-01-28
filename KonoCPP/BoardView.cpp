#include "BoardView.h"

BoardView::BoardView()
{
}

BoardView::~BoardView()
{
}


//void test() {
//    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
//    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    CONSOLE_CURSOR_INFO cursorInfo;
//    cursorInfo.dwSize = 100;
//    cursorInfo.bVisible = FALSE;
//    SetConsoleCursorInfo(hstdout, &cursorInfo);
//
//    // Remember default colors.
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    GetConsoleScreenBufferInfo(hstdout, &csbi);
//
//    // Define choices diplayed to the user.
//    int curItem = 0;
//    int key = 0;
//    while (1) {
//        system("cls");
//        cout << msg << "\n\n";
//        for (int i = 0; i < options.size(); i++)
//        {
//            if (curItem == i) {
//                // Change console colors if this is the selected item.
//                SetConsoleTextAttribute(hstdout, 0x70);
//            }
//            else {
//                // Make sure colors are normal for unselected items.
//                SetConsoleTextAttribute(hstdout, 0x07);
//            }
//            // Print the next menu item.
//            cout << options[i];
//            SetConsoleTextAttribute(hstdout, 0x07);
//            cout << "\n";
//        }
//
//        // Wait for a keypress.
//        switch (key = _getch()) {
//
//            // Arrow keys throw 2 key codes.
//        case 224:
//            switch (key = _getch()) {
//
//                // Up arrow.
//            case 72:
//                if (curItem > 0) {
//                    curItem--;
//                }
//                continue;
//
//                // Down arrow.
//            case 80:
//                if (curItem < options.size() - 1) {
//                    curItem++;
//                }
//                continue;
//            }
//            continue;
//
//            // Enter.
//        case 13:
//            system("cls");
//
//            // Set colors back to default.
//            SetConsoleTextAttribute(hstdout, csbi.wAttributes);
//            cursorInfo.bVisible = TRUE;
//            SetConsoleCursorInfo(hstdout, &cursorInfo);
//            return curItem;
//
//        default:
//            continue;
//        };
//    }
//}




void BoardView::Draw(Board boardObj) const
{
    // Define board and player colors.
    const WORD boardColor = 0x87;
    const WORD wColor     = 0x70;
    const WORD wColorCap  = 0xF0;
    const WORD bColor     = 0x07;
    const WORD bColorCap  = 0x0F;

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
    SetConsoleTextAttribute(hstdout, boardColor);
    cout << 'N';
    for (int i = 0; i < boardSize; i++) {
        cout << "\n" << i + 1 << "   ";
        for (int j = 0; j < boardSize; j++) {
            WORD outputColor = boardColor;
            Piece occupant = board[i][j].occupant;
            if (occupant.GetColor() == 'W' && !occupant.CanCapture()) {
                outputColor = wColor;
            }
            else if (occupant.GetColor() == 'W' && occupant.CanCapture()) {
                outputColor = wColorCap;
            }
            else if (occupant.GetColor() == 'B' && !occupant.CanCapture()) {
                outputColor = bColor;
            }
            else if (occupant.GetColor() == 'B' && occupant.CanCapture()) {
                outputColor = bColorCap;
            }

            // Set board output colors depending on the piece.
            SetConsoleTextAttribute(hstdout, outputColor);

            switch (board[i][j].occupant.GetColor()) {
            case 'W':
            case 'B':
                cout << occupant.GetColor();
                break;
            default:
                cout << '+';
            }

            // Reset colors back to after the piece is drawn.
            SetConsoleTextAttribute(hstdout, boardColor);
            
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
