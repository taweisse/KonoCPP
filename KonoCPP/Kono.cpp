#include "BoardView.h"
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include <vector>
using namespace std;

int main()
{
    Player player1;
    Human player2;

    Board testBoard(7, player1, player2);
    BoardView testView;
    testView.DrawOwner(testBoard);
    cout << "\n";
    testView.DrawValues(testBoard);
    cout << "\n";
    testView.Draw(testBoard);

    for (int i = 6; i >= 0; i--) {
        testBoard.Move(player2, i, i, "NW");
        testView.Draw(testBoard);
    }
   
    system("pause");
}