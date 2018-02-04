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
    const Player* player1 = &tourn.GetGame().GetPlayer(1);
    const Player* player2 = &tourn.GetGame().GetPlayer(2);

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
    vector<vector<Board::Cell>> curBoard = tourn.GetGame().GetBoard().GetBoardArray();
    int boardSize = tourn.GetGame().GetBoard().GetSize();
    outFile << "Board:";
    for (int i = 0; i < boardSize; i++) {
        // New line for each new row.
        outFile << "\n   ";
        for (int j = 0; j < boardSize; j++) {
            Piece thisPiece = curBoard[i][j].occupant;

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
    if (tourn.GetGame().GetPlayer(next).GetType() == Player::human && next == 2) {
        outFile << "Human 2";
    }
    else if (tourn.GetGame().GetPlayer(next).GetType() == Player::human && next == 1) {
        outFile << "Human";
    }
    else {
        outFile << "Computer";
    }

    // Write the buffer and close the file.
    outFile.close();
    return true;
}

bool Serializer::UnserializeFromFile(const Tournament& tourn, const string& filename)
{
    return true;
}