#pragma once
#include "Helpers.h"
#include "Piece.h"

class BoardCell
{
public:
    BoardCell(helpers::Color = helpers::NullColor, Piece = Piece(), int = 0);

    inline void SetColor(helpers::Color color) {
        m_owner = color;
    }

    inline void SetPiece(Piece piece) {
        m_occupant = piece;
    }

    inline void SetValue(int value) {
        m_value = value;
    }

    inline const helpers::Color GetOwner() const {
        return m_owner;
    }

    inline const Piece GetOccupant() const {
        return m_occupant;
    }

    inline const int GetValue() const {
        return m_value;
    }

private:
    helpers::Color m_owner;
    Piece m_occupant;
    int m_value;
};

