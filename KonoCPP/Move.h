#pragma once
#include <string>
using namespace std;

class Move
{
public:
    enum Action { Play, Quit, Save, Help };
    enum ActionReason { Escape = 3, Capture = 2, Advance = 1, Null = -1 };
    enum Direction { NW, NE, SE, SW, NullDir };

    // Constructors. Default, an actual move, and an action - only.
    Move(const Action& = Play);
    Move(const int&, const int&, const Direction&, const Action&, const ActionReason& = Null, const int& tarR = -1, const int& tarC = -1);

    // Check to see if this is a valid action.
    const bool IsValid() const {
        if (m_row <= 0 || m_col <= 0) {
            return false;
        }
        return true;
    }

    void SetMove(const int&, const int&, const Direction&, const Action&, const ActionReason&, const int&  = -1, const int&  = -1);
    
    // Access to all of the private variables:
    const int GetRow() const {
        return m_row;
    }

    const int GetCol() const {
        return m_col;
    }

    const Direction GetDir() const {
        return m_dir;
    }

    const Action GetAction() const {
        return m_action;
    }

    const ActionReason GetReason() const {
        return m_reason;
    }

    const int GetTargetRow() const {
        return m_tarRow;
    }

    const int GetTargetCol() const {
        return m_tarCol;
    }

private:
    int m_row;
    int m_col;
    Direction m_dir;
    Action m_action;
    ActionReason m_reason;

    // The target of the move. (What we are moving towards / away from.)
    int m_tarRow;
    int m_tarCol;
};

