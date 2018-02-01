#include "Serializer.h"

Serializer::Serializer()
{
}

Serializer::~Serializer()
{
}

int Serializer::SerializeToFile(const Tournament& tourn, const string& filename)
{
    ofstream outFile;
    outFile.open(filename);
    // Save the current round.
    outFile << "Round: " << tourn.GetRound() << "\n\n";

    // Save the each player's current score. Note player 2 comes first.
    outFile << tourn.GetPlayer2().GetTypeAsString() << ": \n";
    outFile << "   Score: " << tourn.GetPlayer2Score() << "\n";
    outFile << "   Color: ";

    return 0;
}

int Serializer::UnserializeFromFile(const Tournament& tourn, const string& filename)
{
    return 0;
}
