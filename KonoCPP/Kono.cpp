#include "BoardView.h"
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Game.h"
#include <vector>
using namespace std;

void DisplayLogo();

int main()
{
    system("cls");
    DisplayLogo();

    Board board(5);
    BoardView boardView;

    Human player1('W');
    Human player2('B');

    while (1) {
        boardView.Draw(board);
        player1.PrePlay(board);

        boardView.Draw(board);
        player2.PrePlay(board);
    }   
}

void DisplayLogo() {
    cout << endl;
    cout << "  db   dD .d88b.  d8b   db  .d88b.  \n";
    cout << "  88 ,8P'.8P  Y8. 888o  88 .8P  Y8. \n";
    cout << "  88,8P  88    88 88V8o 88 88    88 \n";
    cout << "  88`8b  88    88 88 V8o88 88    88 \n";
    cout << "  88 `88.`8b  d8' 88  V888 `8b  d8' \n";
    cout << "  8P   YD `Y88P'  8P   V8P  `Y88P'  \n\n";
}