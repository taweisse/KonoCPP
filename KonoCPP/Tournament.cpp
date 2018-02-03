#include "Tournament.h"

Tournament::Tournament()
{
}

Tournament::~Tournament()
{
}

bool Tournament::PlayTournament()
{
    return true;
}

int Tournament::ThrowDice()
{
    // Seed the random number generator.
    srand((int)time(NULL));

    int p1Sum, p2Sum;
    do {
        int lineNum = 1;
        int rolls[4];

        // If no dice file is specified, roll 4 random numbers.
        if (m_diceFile.length() == 0) {
            for (int i = 0; i < 4; i++) {
                rolls[i] = rand() % 6 + 1;
            }
        }
        else {
            cout << "We don't support dice from a file yet.";
            system("pause");
            exit(0);
        }

        p1Sum = rolls[0] + rolls[1];
        p2Sum = rolls[2] + rolls[3];

        cout << "Roll the dice, Player 1! ";
        system("pause");
        cout << rolls[0] << " " << rolls[1] << "\n\n";

        cout << "Roll the dice, Player 2! ";
        system("pause");
        cout << rolls[2] << " " << rolls[3] << "\n\n";

        if (p1Sum == p2Sum) {
            cout << "Tie!\n\n";
        }
        else if (p1Sum > p2Sum) {
            cout << "Player 1 plays first. \n";
        }
        else {
            cout << "Player 2 plays first. \n";
        }
    } while (p1Sum == p2Sum);

    // Return the player with the larger sum.
    return (p1Sum > p2Sum ? 1 : 2);
}