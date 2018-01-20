#include "BoardView.h"
#include <vector>
using namespace std;

int main()
{
    vector<vector<char>> board{
        { 'B','W','B' },
        {  0,  0,  0  },
        { 'B','W','B' }
    };

    BoardView test;
    test.DisplayBoard(board);
    system("pause");
}