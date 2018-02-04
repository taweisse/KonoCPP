#include "Computer.h"

Computer::Computer(const helpers::Color& color, const int& pts)
{
    m_color = color;
    m_points = pts;
}

const Move Computer::PrePlay(Board& board)
{
    Move thisMove;
    int choice = helpers::ShowMenu("Please select an option:", { "Save & Exit", "Make a Move", "Quit Game" });
    if (choice == 1) {
        thisMove = Move(Move::Save);
    }
    else {
        thisMove = Play(board);
    }

    if (thisMove.GetAction() == Move::Play) {
        "The computer has a good move and would like to keep playing. \n";
    }

    // Return the move that we just played.
    return thisMove;
}

