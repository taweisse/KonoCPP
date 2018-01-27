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

    Board testBoard(5);
    BoardView testView;
    testView.DrawOwner(testBoard);
    cout << "\n";
    testView.DrawValues(testBoard);
    cout << "\n";

    while (1) {
        testView.Draw(testBoard);
        player1.Play(testBoard);
        player2.Play(testBoard);

        cout << "Player1 Points: " << player1.GetPoints() << endl;
        cout << "Player2 Points: " << player2.GetPoints() << endl;
    }   
}