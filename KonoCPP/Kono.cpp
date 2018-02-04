#include "Tournament.h"
#include "Serializer.h"
#include "Helpers.h"
using namespace std;

void DisplayLogo();

int main()
{
    // Loop until the user exits.
    while (1) {
        system("cls");
        DisplayLogo();

        // All games will occur within this tournament object.
        Tournament thisTournament;

        // Passed to the tournament object to tell it what types of players we have.
        Player::PlayerType p1Type = Player::human;
        Player::PlayerType p2Type = Player::player;

        // Ask the user what they want to do.
        string filename;
        switch (helpers::ShowMenu("Welcome! What do you want to do?", { "Start a New Tournament", "Load a Saved Tournament", "Exit" })) {
        case 1:
            // Start a new tournament. First, determine the human's opponent.
            cout << "\n";
            switch (helpers::ShowMenu("Who do you want to play against?", { "Human", "Computer" })) {
            case 1:
                p2Type = Player::human;
                break;
            default:
                p2Type = Player::computer;
                break;
            }
            // Create a new tournement based on the human's opponent type.
            thisTournament = Tournament(p1Type, p2Type);
            break;
        case 2:
            cout << "Please enter a filename to load from: \n";
            getline(cin, filename);
            if (Serializer::UnserializeFromFile(thisTournament, filename)) {
                system("pause");
                exit(0);
                // WE NEED TO ACTUALLY break; HERE!!! - to then go and play the tournament.
            }
            else {
                cout << "Can't load file.";
                system("pause");
            }
        default:
            exit(0);
        }
        cout << "\n";

        // Start the tournament. The tournament object will take care of the rest. When it has ended,
        // we will ask the user if they would like to play again.
        bool isComplete = thisTournament.PlayTournament();
        if (!isComplete) {
            // if the tournament is not complete, serialize it here.
            string filename;
            cout << "Please enter a filename to save to: \n";
            getline(cin, filename);

            bool didSave = Serializer::SerializeToFile(thisTournament, filename);
            if (didSave) {
                cout << "File saved successfully. ";
            }
            else {
                cout << "Error saving file. ";
            }
            system("pause");
            exit(0);
        }
    }


    vector<string> testData = { "B", "B", "B", "B", "B", "B", "O", "O", "O", "O", "O", "O", "O", "B", "O", "WW", "O", "W", "B", "WW", "O", "O", "O", "O", "O" };
    Board t1(testData);
    BoardView testView;


    Human p1(helpers::White);
    Human p2(helpers::Black);

    Game game(p1, p2, 2, testData);
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