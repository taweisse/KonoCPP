#include "BoardView.h"
#include "Board.h"
#include <vector>
using namespace std;

int main()
{
    Board testBoard(5);
    BoardView testView;
    testView.Draw(testBoard);
    system("pause");
}