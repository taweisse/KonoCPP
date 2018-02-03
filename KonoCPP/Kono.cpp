#include "BoardView.h"
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Game.h"
#include <vector>
#include "Helpers.h"
using namespace std;

void DisplayLogo();

int main()
{
    vector<string> testData = { "O", "W", "W", "W", "B", "O", "O", "WW", "WW", "B", "BB", "O", "O", "O", "O", "WW", "O", "W", "B", "WW", "O", "O", "O", "O", "O" };
    Board t1(testData);
    BoardView testView;
    testView.Draw(t1);
    system("pause");

    system("cls");
    DisplayLogo();

    Human p1(helpers::White);
    Human p2(helpers::Black);
    Game game(p1, p2, 2);
    game.PlayGame();
    system("pause");
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