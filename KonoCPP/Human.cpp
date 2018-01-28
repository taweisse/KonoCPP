#include "Human.h"

Human::Human()
{
}

Human::~Human()
{
}

void Human::Play(Board& board) 
{
    // Get coordinates of the move.
    int row, col;
    char dir[3];
    while (1) {
        cout << "Enter Row: \n";
        if (ReadDigit(row) && row > 0 && row <= board.GetSize()) {
            break;
        }
        cout << "Entry invalid. ";
    }
    while (1) {
        cout << "Enter Column: \n";
        if (ReadDigit(col) && col > 0 && col <= board.GetSize()) {
            break;
        }
        cout << "Entry invalid. ";
    }
    // Get direction of the move.
    while (1) {
        cout << "Enter move direction: ( NW, NE, SE, SW ) \n";
        if (ReadDirection(dir)) {
            break;
        }
        cout << "Direction invalid. ";
    }

    cout << "\nHere's what your move looks like: \nRow: " << row << " Col: " << col << " " << dir << "\n\n";

    // Perform the move.
    int pts = 0;
    try {
        board.Move(row, col, dir, pts);
        m_points += pts;
    }
    catch (exception) {
        cout << "That move was invalid. \n";
    }
}

// Helper function to read a single digit from the console.
// Returns true if successful.
bool ReadDigit(int& digit) 
{
    string input;
    getline(cin, input);

    // Make sure the user only entered a single character.
    if (input.length() > 1) {
        return false;
    }

    // Make sure the user entered a digit. If they did, convert it.
    char num = input[0];
    if (!isdigit(num)) {
        return false;
    }
    digit = atoi(&num);
    return true;
}

// Helper function to read a compass direction from the console.
// Returns true if successful.
bool ReadDirection(char dir[3]) 
{
    string input;
    getline(cin, input);

    // Make sure the user only entered 2 characters.
    if (input.length() != 2) {
        return false;
    }

    // Make sure the user entered alpha characters, and convert to uppercase if they did.
    for (int i = 0; i < 2; i++) {
        if (!isalpha(input[i])) {
            return false;
        }
        input[i] = toupper(input[i]);
    }

    // Make sure the input is a valid direction.
    if ((input[0] != 'N' && input[0] != 'S') || (input[1] != 'E' && input[1] != 'W')) {
        return false;
    }

    strcpy_s(dir, 3, input.c_str());
    return true;
}