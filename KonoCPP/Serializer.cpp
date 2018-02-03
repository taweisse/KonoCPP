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

    return 0;
}

int Serializer::UnserializeFromFile(const Tournament& tourn, const string& filename)
{
    return 0;
}
