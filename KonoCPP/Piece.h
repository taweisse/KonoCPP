#pragma once
#include <stdexcept>
#include "Helpers.h"

class Piece
{
public:
    Piece() {
        m_color = helpers::NullColor;
        m_canCapture = false;
    }

    Piece(helpers::Color color) {
        if (color == helpers::White || color == helpers::Black) {
            m_color = color;
        }
        else {
            m_color = helpers::NullColor;
        }
        m_canCapture = false;
    }

    ~Piece();

    inline const helpers::Color GetColor() const {
        return m_color;
    }

    inline const bool CanCapture() const {
        return m_canCapture;
    }

    inline const bool IsEmpty() const {
        return (m_color == helpers::NullColor ? true : false);
    }

    // Upgrade the piece to allow it to capture opponents.
    inline void AllowCapture() {
        m_canCapture = true;
    }

private:
    helpers::Color m_color;
    bool m_canCapture;
};

