#include "Serializer.h"

bool Serializer::SerializeToFile(const Tournament& tourn, const string& filename)
{
    // Open a file to save our data to.
    ofstream outFile;
    outFile.open(filename);

    // Save the current round.
    outFile << "Round: " << tourn.GetRound() << "\n\n";
    
    // Save player information. Since the game allows for 2 humans to play one another, player 2 will
    // always come first in the file. If there are 2 humans, the text file will read 'Human 2',
    // followed by 'Human', in order to keep the format consistent with the game description.
    const Player* player1 = tourn.GetGame().GetPlayer(1);
    const Player* player2 = tourn.GetGame().GetPlayer(2);

    // Player 2 can be a human or computer. Handle both cases here.
    if (player2->GetType() == Player::computer) {
        outFile << "Computer:\n";
    }
    else {
        outFile << "Human 2:\n";
    }
    outFile << "   Score: " << tourn.GetPlayerScore(2) << "\n";
    outFile << "   Color: ";

    // Might as well save player 1's color while we find player 2's since it will always be opposite.
    string p1Color;
    if (player2->GetColor() == helpers::White) {
        outFile << "White";
        p1Color = "Black";
    }
    else {
        outFile << "Black";
        p1Color = "White";
    }
    outFile << "\n\n";

    // Player 1 will always be a human.
    outFile << "Human:\n   Score: " << tourn.GetPlayerScore(1) << "\n   Color: " << p1Color << "\n\n";

    // Write the board data.
    int boardSize = tourn.GetGame().GetBoard().GetSize();
    outFile << "Board:";
    for (int i = 1; i <= boardSize; i++) {
        // New line for each new row.
        outFile << "\n   ";
        for (int j = 1; j <= boardSize; j++) {
            Piece thisPiece = tourn.GetGame().GetBoard().GetOccupant(i, j);

            // Represent super pieces with 2 characters instead of one.
            if (thisPiece.CanCapture()) {
                outFile << (char)thisPiece.GetColor() << (char)thisPiece.GetColor() << " ";
            }
            else {
                outFile << (char)thisPiece.GetColor() << "  ";
            }
        }
    }
    outFile << "\n\n";

    // Save the next player in the game.
    outFile << "Next Player: ";
    int next = tourn.GetGame().GetNextPlayer();
    // Remember that if player 2 is also a human, we will refer to him as 'Human 1' to avoid
    // confusion.
    if (next == 1) {
        outFile << "Human";
    }
    else if (player2->GetType() == Player::human) {
        outFile << "Human 2";
    }
    else {
        outFile << "Computer";
    }

    // Write the buffer and close the file.
    outFile.close();
    return true;
}

bool Serializer::UnserializeFromFile(Tournament& tourn, const string& filename)
{
    // The variables that we will need to extract from the serialized file. Initializing them to 
    // invlaid values will allow us to check if there were any errors reading the serialized file.
    Player::PlayerType p1Type = Player::player, p2Type = Player::player;
    vector<string> boardData;
    helpers::Color p1Color = helpers::NullColor, p2Color = helpers::NullColor;
    int round = -1, p1Score = -1, p2Score = -1, nextPlayer = -1;

    // Open our file.
    ifstream inFile(filename);

    // Loop while there are lines to be read.
    string line, word;
    while (getline(inFile, line)) {
        // Ignore blank lines.
        if (line == "") {
            continue;
        }

        istringstream words(line);
        words >> word;

        // Parse the round.
        if (word == "Round:") {
            words >> round;
            continue;
        }
        // Parse player 1. He will always be human.
        else if (word == "Human:") {
            // Load the player's data.
            p1Type = Player::human;
            LoadPlayerData(inFile, p1Score, p1Color);
        }
        // If player 2 is a human, he will labeled 'Human 2'.
        else if (word == "Human") {
            words >> word;
            // If the player is not labeled 'Human 2', there is an issue with the file.
            if (word != "2:") {
                return false;
            }
            // Load the player's data.
            p2Type = Player::human;
            LoadPlayerData(inFile, p2Score, p2Color);
        }
        else if (word == "Computer:") {
            // Load the player's data.
            p2Type = Player::computer;
            LoadPlayerData(inFile, p2Score, p2Color);
        }
        else if (word == "Board:") {
            LoadBoardData(inFile, boardData);
        }
        // Figure out who the next player is. 
        else if (word == "Next") {
            words >> word;
            // 'Next' should always be followed by 'Player:'. If not, bad file.
            if (word != "Player:") {
                return false;
            }
            // Load the next player data.
            words >> word;
            if (word == "Human") {
                // We can either have 'Human' or 'Human 2' here, so figure out which one.
                words >> word;
                if (word == "Human") {
                    // If just 'Human' is printed, we know it is player 1.
                    nextPlayer = 1;
                }
                else if (word == "2") {
                    // If 'Human 2' is printed, we know it is player 2.
                    nextPlayer = 2;
                }
            }
            // 'Computer' will always be player 2.
            else if (word == "Computer") {
                nextPlayer = 2;
            }
        }
    }
    // Close the file.
    inFile.close();

    // Check to make sure that all values were successfully read from the file. If any are missing, we
    // will return false to indicate that the file was not read successfully.
    if (p1Type == Player::player || p2Type == Player::player) {
        return false;
    }
    else if (p1Color == helpers::NullColor || p2Color == helpers::NullColor) {
        return false;
    }
    else if (round == -1 || p1Score == -1 || p2Score == -1 || nextPlayer == -1) {
        return false;
    }

    // Contruct the board object for the resumed game. The board constructor will throw an exception
    // if the board data that we read was bad.
    int whiteGamePts = 0, blackGamePts = 0; // Variables will be updated by the board constructor to reflect what
                                            // point values each color player would have.
    Board loadedBoard;
    try {
        loadedBoard = Board(boardData, whiteGamePts, blackGamePts);
    }
    catch (invalid_argument) {
        // Return not successful if the board data from the file was invalid.
        return false;
    }

    int p1GamePoints, p2GamePoints;
    if (p1Color == helpers::White) {
        p1GamePoints = whiteGamePts;
        p2GamePoints = blackGamePts;
    }
    else {
        p1GamePoints = blackGamePts;
        p2GamePoints = whiteGamePts;
    }

    // Construct the correct players for this game. Player 1 will always be a human.
    Player* player1 = new Human(p1Color, p1GamePoints);

    // Decide which type player 2 is.
    Player* player2;
    if (p2Type == Player::human) {
        player2 =  new Human(p2Color, p2GamePoints);
    }
    else {
        player2 =  new Computer(p2Color, p2GamePoints);
    }
    
    // Construct the game object from our board and players.
    Game loadedGame(*player1, *player2, nextPlayer, loadedBoard);

    // Construct the tournament from the game.
    tourn = Tournament(p1Type, p2Type, loadedGame, round, p1Score, p2Score, nextPlayer);

    // Return that the game loaded successfully.
    return true;
}

void Serializer::LoadPlayerData(ifstream& inFile, int& score, helpers::Color& color) 
{
    string line, word;

    // Read 2 lines from the input file.
    for (int i = 0; i < 2; i++) {
        getline(inFile, line);
        istringstream words(line);
        // For each line, parse the relevant data. We are looking to get a player color and score 
        // from these two lines.
        words >> word;
        if (word == "Score:") {
            // Load player's score.
            words >> score;
            continue;
        }
        // If the word is not score, it must be color.
        words >> word;
        if (word == "White") {
            color = helpers::White;
        }
        else if (word == "Black") {
            color = helpers::Black;
        }
    }
}

void Serializer::LoadBoardData(ifstream& inFile, vector<string>& data) 
{
    // Make sure the data array is empty.
    data.clear();
 
    // Read until we hit a blank line, AKA end of the board.
    string line, word;
    while (getline(inFile, line)) {
        // Return when we hit the end of the board.
        if (line == "") {
            return;
        }
        // Split each line on spaces. 
        istringstream words(line);
        while (getline(words, word, ' ')) {
            if (word != "") {
                data.push_back(word);
            }
        }
    }
}