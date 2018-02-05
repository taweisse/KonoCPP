#include "BoardCell.h"

BoardCell::BoardCell(helpers::Color owner, Piece occupant, int value) {
    m_owner = owner;
    m_occupant = occupant;
    m_value = value;
}
