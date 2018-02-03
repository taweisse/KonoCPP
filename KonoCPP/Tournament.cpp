#include "Tournament.h"

Tournament::Tournament(Player::PlayerType p1, Player::PlayerType p2, Game game, int round, int p1Score, int p2Score, int first)
{
    m_currentGame = game;
    m_roundNum = round;
    m_p1Type = p1;
    m_p2Type = p2;
    m_p1Score = p1Score;
    m_p2Score = p2Score;
    m_firstPlayer = first;
}

Tournament::~Tournament()
{
}

bool Tournament::PlayTournament()
{
    // If the round number is 0, this is a brand new tournament. // Decide who plays first based on 
    // a dice roll.
    if (m_roundNum == 0) {
        m_firstPlayer = ThrowDice();
    }

    // Pointers used to reference the players
    Player* player1 = nullptr;
    Player* player2 = nullptr;
    
    // If the current game is not initialized, initialize it.
    if (!m_currentGame.IsInitialized()) {
        ConfigureGame(player1, player2);
        m_roundNum++;
        // Tell the user that which round we are on.
        cout << "Starting round #" << m_roundNum << "\n";
    }
    else {
        // Tell the user that which round we are on.
        cout << "Resuming round #" << m_roundNum << "\n";
    }
    
    // Play the game.
    bool isComplete = m_currentGame.PlayGame();

    // If the game was completed successfully, we can ask the player if they want to play another.
    // If unsuccessful, a player chose to save and quit, so we need to serialize.
    if (isComplete) {
        cout << "Display winnings information here. Ask if user wants to play again.\n\n";
    }
    else {
        cout << "User chose to serialize the game. Do that here.\n";
    }

    system("pause");

    // Clean up the previous game's player objects.
    delete player2;
    delete player1;

    system("pause");
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

        cout << "Player 1 rolls " << rolls[0] << " " << rolls[1] << "\n";
        cout << "Player 2 rolls " << rolls[2] << " " << rolls[3] << "\n\n";

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

void Tournament::ConfigureGame(Player*& p1, Player*& p2)
{
    // In case we were passed a player pointer that had already been used, make sure we free the
    // old allocated memory.
    delete p1;
    delete p2;
    p1 = nullptr;
    p2 = nullptr;

    // Let player 1 pick his color for this game.
    helpers::Color p1Color, p2Color;
    string menuTitle = "Select a color, Player " + to_string(m_firstPlayer) + ":";
    int colorChoice = helpers::ShowMenu(menuTitle, { "White", "Black" });
    if ((colorChoice == 1 && m_firstPlayer == 1) || (colorChoice == 2 && m_firstPlayer == 2)) {
        p1Color = helpers::White;
        p2Color = helpers::Black;
    }
    else if ((colorChoice == 1 && m_firstPlayer == 2) || (colorChoice == 2 && m_firstPlayer == 1)) {
        p1Color = helpers::Black;
        p2Color = helpers::White;
    }
    else {
        throw invalid_argument("There is a bug in the game configuration somewhere.");
    }
    cout << "\n";

    // Ask the user how big of a board they want.
    int size = helpers::ShowMenu("Select a board size for this game:", { "5 x 5", "7 x 7", "9 x 9" });
    cout << "\n";

    // Create new player objects for this game.
    p1 = new Human(p1Color);
    if (m_p2Type == Player::human) {
        p2 = new Human(p2Color);
    }
    else if (m_p2Type == Player::computer) {
        p2 = new Computer(p2Color);
    }
    else {
        throw invalid_argument("Player 2 must have type human or computer.");
    }

    // Create the game for this round.
    m_currentGame = Game(*p1, *p2, m_firstPlayer, Board(((size + 1) * 2) + 1));
}