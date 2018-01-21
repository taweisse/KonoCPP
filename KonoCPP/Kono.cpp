#include "BoardView.h"
#include "Board.h"
#include <vector>
using namespace std;

int main()
{
    Board testBoard(9);
    BoardView testView;
    testView.Draw(testBoard);
    cout << "\n";
    testView.DrawValues(testBoard);

    system("pause");
}