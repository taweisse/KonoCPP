#pragma once
#include "BoardView.h"
#include "Board.h"
#include "Player.h"
//#include "Human.h"
#include <vector>
using namespace std;

int main()
{
    Player player1;
    Player player2;

    Board testBoard(7, player1, player2);
    BoardView testView;
    testView.DrawOwner(testBoard);
    cout << "\n";
    testView.DrawValues(testBoard);
    cout << "\n";
    testView.Draw(testBoard);

    while (1) {
        player1.Play(testBoard);
        player2.Play(testBoard);
    }
}