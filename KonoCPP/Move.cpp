#include "Move.h"

Move::Move(const Action& action)
{
    // Constructor assigns negative to row and column to test if this move is valid.
    m_row = -1;
    m_col = -1;
    m_dir = NW;
    m_reason = Null;
}

Move::Move(const int& row, const int& col, const Direction& dir, const Action& action, const ActionReason& reason)
{
    SetMove(row, col, dir, action, reason);
}

Move::~Move()
{

}

void Move::SetMove(const int& row, const int& col, const Direction& dir, const Action& action, const ActionReason& reason)
{
    if (row > 0 && col > 0) {
        m_row = row;
        m_col = col;
    }
    m_dir = dir;
    m_action = action;
    m_reason = reason;
}
