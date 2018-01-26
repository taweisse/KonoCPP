#pragma once
#include <stdexcept>

class Piece
{
public:
    Piece() {
        m_color = 'O';
        m_canCapture = false;
    }

    Piece(char color) {
        if (color == 'B' || color == 'W') {
            m_color = color;
            m_canCapture = false;
        }
        else {
            //throw invalid_argument("Invalid color.");
        }
    }

    ~Piece();

    inline const char GetColor() const {
        return m_color;
    }

    inline const bool CanCapture() const {
        return m_canCapture;
    }

    int i = 0;
    inline const bool IsEmpty() const {
        return (m_color == 'O' ? true : false);
    }

    // Upgrade the piece to allow it to capture opponents.
    inline void AllowCapture() {
        m_canCapture = true;
    }

private:
    char m_color;
    bool m_canCapture;
};

