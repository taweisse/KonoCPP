//#include "Human.h"
//
//Human::Human()
//{
//}
//
//Human::~Human()
//{
//}
//
//void Human::Play(Board& board)
//{
//    // Get coordinates of the move.
//    int row, col;
//    cout << "Enter Row: \n";
//    cin >> row;
//    cout << "Enter Colummn: \n";
//    cin >> col;
//
//    // Get direction of the move.
//    char dir[2];
//    cout << "Enter move direction: ( NW, NE, SE, SW ) \n";
//    cin >> dir;
//
//    // Move 
//    try {
//        board.Move(*this, row - 1, col - 1, dir);
//    }
//    catch (exception) {
//        cout << "That move was invalid. \n";
//    }
//}