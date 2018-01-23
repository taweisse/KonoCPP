#include "BoardView.h"
#include "Board.h"
#include <vector>
using namespace std;

int main()
{
    Board testBoard(5);
    BoardView testView;
    testView.DrawOwner(testBoard);
    cout << "\n";
    testView.DrawValues(testBoard);
    cout << "\n";
    testView.Draw(testBoard);

    system("pause");
}