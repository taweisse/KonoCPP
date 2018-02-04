#include "Tournament.h"

Tournament::Tournament(Player::PlayerType p1, Player::PlayerType p2, Game game, int round, int p1Score, int p2Score, int first)
{
    m_currentGame = game;
    m_roundNum = round;
    m_players[0].m_type = p1;
    m_players[1].m_type = p2;
    m_players[0].m_score = p1Score;
    m_players[1].m_score = p2Score;
    m_firstPlayer = first;
}

Tournament::~Tournament()
{
}

bool Tournament::PlayTournament()
{
    // Pointers used to reference the players of each game.
    Player* player1 = nullptr;
    Player* player2 = nullptr;

    // Loop until the user does not want to play anymore.
    while (1) {
        // If the round number is 0, this is a brand new tournament. Decide who plays first based on 
        // a dice roll.
        if (m_roundNum == 0) {
            m_firstPlayer = ThrowDice();
        }
        else {
            cout << "Player " << m_firstPlayer << " won last round. He will move first.\n";
        }

        // If the current game is not initialized, initialize it.
        if (!m_currentGame.IsInitialized()) {
            ConfigureGame(player1, player2);
            m_roundNum++;
            cout << "Starting";
        }
        else {
            cout << "Resuming";
        }
        cout << " round #" << m_roundNum << "\n";

        // Play the game.
        bool isComplete = m_currentGame.PlayGame();

        // If the game was completed successfully, we can ask the player if they want to play another.
        // If unsuccessful, a player chose to save and quit, so we need to serialize.
        if (isComplete) {
            // Get the final number of points that each player wound up with.
            int p1Points = m_currentGame.GetPlayer(1).GetPoints();
            int p2Points = m_currentGame.GetPlayer(2).GetPoints();

            if (p1Points == p2Points) {
                cout << "The game was a tie! Neither player will recieve points this round. \n\n";
            }
            else {
                int ptsEarned = abs(p1Points - p2Points);

                // Tell the user what the final score was.
                cout << "\n";
                cout << "Player 1 scored " << p1Points << "\n";
                cout << "Player 2 scored " << p2Points << "\n";
                int winner = (p1Points > p2Points) ? 1 : 2;

                // Add the points from this round to the player's total score.
                cout << "Player " << winner << " wins and gets " << ptsEarned << " points this round. \n\n";
                m_players[winner - 1].m_score += ptsEarned;
                
                // Display the total points of the tournament.
                for (int i = 0; i < 2; i++) {
                    cout << "Player " << i + 1 << " has accumulated " << m_players[i].m_score << " points in this tournament.\n";
                }
                cout << "\n";

                // Set the starting player for the next game to the winner.
                m_firstPlayer = winner;
            }
            // Ask if the user wants to play another game.
            int anotherChoice = helpers::ShowMenu("Would you like to play another round?", { "Yes", "No" });
            if (anotherChoice == 1) {
                m_currentGame = Game();
                continue;
            }
            else {
                break;
            }
        }
        // Game was not complete. User wants to serialize the game.
        else {
            // Returning false lets the caller know that this tournament is not complete, and so to 
            // serialize it.
            return false;
        }
    }
    
    cout << "\n";
    if (m_players[0].m_score == m_players[1].m_score) {
        cout << "The tournament is a tie! \n";
        cout << "Both players accumulated " << m_players[0].m_score << " points in this tournament.\n\n";
    }
    else {
        int tournWinner = (m_players[0].m_score > m_players[1].m_score) ? 1 : 2;
        int tournLoser = (tournWinner == 1) ? 2 : 1;
        cout << "Player " << tournWinner << " wins the tournament " << m_players[tournWinner - 1].m_score << " - " << m_players[tournLoser - 1].m_score << "!";
        cout << "\n\n";
    }


    system("pause");

    // Clean up the previous game's player objects.
    delete player2;
    delete player1;
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
    if (m_players[1].m_type == Player::human) {
        p2 = new Human(p2Color);
    }
    else if (m_players[1].m_type == Player::computer) {
        p2 = new Computer(p2Color);
    }
    else {
        throw invalid_argument("Player 2 must have type human or computer.");
    }

    // Create the game for this round.
    m_currentGame = Game(*p1, *p2, m_firstPlayer, Board(((size + 1) * 2) + 1));
}