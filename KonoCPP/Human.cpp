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
    cout << "Enter Row: \n";
    ReadDigit(row);
    cout << "Enter Colummn: \n";
    ReadDigit(col);
    
    // Get direction of the move.
    char dir[3];
    cout << "Enter move direction: ( NW, NE, SE, SW ) \n";
    ReadDirection(dir);
    
    // Move 
    try {
        m_points += board.Move(row - 1, col - 1, dir);
    }
    catch (exception) {
        cout << "That move was invalid. \n";
    }
}

// Helper function to read a single digit from the console.
// Returns true if successful.
bool ReadDigit(int& digit) {
    return true;
}

// Helper function to read a compass direction from the console.
// Returns true if successful.
bool ReadDirection(char dir[3]) {
    return true;
}