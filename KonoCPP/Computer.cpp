#include "Computer.h"

Computer::Computer(const helpers::Color& color, const int& pts)
{
    m_color = color;
    m_points = pts;
}

const Move Computer::PrePlay(Board& board)
{
    Move thisMove;
    Move tmpMove = Play(board);
    
    while (1) {
        int choice = helpers::ShowMenu("Please select an option:", { "Save & Exit", "Make a Move", "Quit Game" });
        switch (choice) {
        case 1:
            return Move(Move::Save);
        case 3:
            if (tmpMove.GetAction() != Move::Quit) {
                cout << "The computer would like to keep playing. \n";
                system("pause");
            }
        case 2:
            if (tmpMove.GetAction() == Move::Quit) {
                return tmpMove;
            }
            else {
                thisMove = Move(tmpMove.GetRow(), tmpMove.GetCol(), tmpMove.GetDir(), Move::Play, tmpMove.GetReason(), tmpMove.GetTargetRow(), tmpMove.GetTargetCol());
                int pts;
                if (board.MakeMove(thisMove, pts) != Board::Null) {
                    cout << "The computer tried to play an invalid move.\n";
                    continue;
                }
                m_points += pts;

                // Return the move that we decided on.
                return thisMove;
            }
        }
    }
}

