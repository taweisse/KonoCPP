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

    Board testBoard(7);
    BoardView testView;
    testView.DrawOwner(testBoard);
    cout << "\n";
    testView.DrawValues(testBoard);
    cout << "\n";

    while (1) {
        testView.Draw(testBoard);
        player1.Play(testBoard);
        player2.Play(testBoard);
    }   
}