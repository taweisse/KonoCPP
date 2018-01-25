#pragma once
#include <stdexcept>
using namespace std;

class Player
{
public:
    Player();
    ~Player();

    // Returns the number of points that the player has accumulated.
    inline const int GetPoints() const {
        return m_points;
    }

    // Adds or subtracts points from the player's score.
    inline void AddPoints(int points) {
        m_points += points;
    }

protected:
    int m_points;
};