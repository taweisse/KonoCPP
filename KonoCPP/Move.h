#pragma once
#include <string>
using namespace std;

class Move
{
public:
    enum Action { Play, Quit };
    enum ActionReason { Block, Advance, Capture, Escape, Null };
    enum Direction { NW, NE, SE, SW };

    Move();
    Move(const int&, const int&, const Direction&, const Action&, const ActionReason& = Null);
    ~Move();

    // Check to see if this is a valid action.
    const bool IsValid() const {
        if (m_row <= 0 || m_col <= 0) {
            return false;
        }
        return true;
    }

    void SetMove(const int& row, const int& col, const Direction& dir, const Action& action, const ActionReason& reason = Null);
    
    // Access to all of the private variables:
    inline const int GetRow() const {
        return m_row;
    }

    inline const int GetCol() const {
        return m_col;
    }

    inline const Direction GetDir() const {
        return m_dir;
    }

    inline const Action GetAction() const {
        return m_action;
    }

    inline const ActionReason GetReason() const {
        return m_reason;
    }

private:
    int m_row;
    int m_col;
    Direction m_dir;
    Action m_action;
    ActionReason m_reason;
};

