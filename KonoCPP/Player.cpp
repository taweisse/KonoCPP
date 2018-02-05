#include "Player.h"

Player::Player()
{
    m_color = helpers::NullColor;
    m_points = 0;
}

Player::~Player()
{
}

const Move Player::PrePlay(Board& board) 
{
    return Play(board);
}

const Move Player::Play(Board& board) 
{
    // Holds an array of moves that we can pick form later.
    vector<Move> possibleMoves;

    // Examine each location on the board.
    int boardSize = board.GetSize();
    for (int row = 1; row <= boardSize; row++) {
        for (int col = 1; col <= boardSize; col++) {
            Piece occupant = board.GetOccupant(row, col);
            
            // If we dont have a piece at this location, skip it.
            if (occupant.GetColor() != m_color) {
                continue;
            }

            // If there is a piece at this location, find the best move available for it and add it 
            // to our list.
            possibleMoves.push_back(BestMove(board, row, col));
        }
    }
    // Pick the best move that we have found, and play it.
    // If we cant find anything better than quit, we will quit.
    Move bestMove = Move(Move::Quit); 

    // Use the values of the enum to rank each move.
    int bestReason = 0;
    for (int i = 0; i < (int)possibleMoves.size(); i++) {
        // Skip invalid moves.
        if (!possibleMoves[i].IsValid()) {
            continue;
        }
        if (possibleMoves[i].GetReason() > bestReason) {
            bestMove = possibleMoves[i];
        }
    }

    // Play the best move we found.
    return bestMove;
}

// Finds and returns the best move at a particular location.
Move Player::BestMove(const Board& board, int r, int c)
{
    // Not being captured is the top priority. First see if there is any risk of being captured
    // if we dont move this piece away.
    for (int i = -1; i <= 1; i++) {
        if (i == 0) {
            continue;
        }
        for (int j = -1; j <= 1; j++) {
            if (j == 0) {
                continue;
            }
            // Get the neighboring piece. If we are off the board, skip it.
            Piece neighbor;
            try {
                neighbor = board.GetOccupant(r + i, c + j);
            }
            catch (exception) {
                continue;
            }
            
            // See if there is an opponent neighboring us. It may be dangerous if they are.
            if (neighbor.GetColor() != m_color && !neighbor.IsEmpty()) {
                // We are going to be captured.
                if (neighbor.CanCapture()) {
                    return MoveToEmptySpace(board, r, c);
                }
                // If we can capture, lets do it. Return the move that will capture the opponent.
                else if (board.GetOccupant(r, c).CanCapture()) {
                    return Move(r, c, GetDirection(i, j), Move::Help, Move::Capture);
                }
            }
            // If there is no threat from an opponent, we should move towards the nearest home location.
            return MoveToHome(board, r, c);
        }
    }
    // If we cant do anything, return an invalid move to signal not to consider this one.
    return Move();
}

// Moves the player at (r, c) to an empty space on the board.
Move Player::MoveToEmptySpace(const Board& board, int r, int c) {
    for (int i = -1; i <= 1; i++) {
        if (i == 0) {
            continue;
        }
        for (int j = -1; j <= 1; j++) {
            if (j == 0) {
                continue;
            }
            // Get the neighboring piece. If we are off the board, skip it.
            Piece neighbor;
            try {
                neighbor = board.GetOccupant(r + i, c + j);
            }
            catch (exception) {
                continue;
            }
            // If a neighboring space is empty, we will move there.
            if (neighbor.IsEmpty()) {
                return Move(r, c, GetDirection(i, j), Move::Help, Move::ActionReason::Escape);
            }
        }
    }
    // If there are no empty spaces to move to, return a null move.
    return Move();
}

// Moves the player at (r, c) towards the nearest home location.
Move Player::MoveToHome(const Board& board, int r, int c) {
    int boardSize = board.GetSize();

    // Stores the position of the nearest home location. We will initialize these to values far 
    // greater than what is possible on our board sizes, so that we can keep track of the lowest 
    // values.
    int closestRow = boardSize * 2;
    int closestCol = boardSize * 2;
    int closestDist = boardSize * 2;
    for (int i = 1; i <= boardSize; i++) {
        for (int j = 1; j <= boardSize; j++) {
            Piece targetPiece = board.GetOccupant(i, j);
            helpers::Color targetOwner = board.GetOwner(i, j);
            // See if the current scan location is an opponent's home cell and if it is empty.
            if (targetOwner != m_color && targetOwner != helpers::NullColor) {
                int dist = GetDistance(r, i, c, j);
                // If the number is odd, no good. This means that we cant actually reach this home
                // location due to the nature of only being able to move diagonally.
                if (dist % 2) {
                    continue;
                }
                // If the number is even, and it is closer than what we've found previously, lets
                // store it as a new low.
                if (dist < closestDist) {
                    closestDist = dist;
                    closestRow = i;
                    closestCol = j;
                }
            }
        }
    }
    // If nothing was found, return null move. We can't get anywhere.
    if (closestDist == boardSize * 2) {
        return Move();
    }
    // Return the move that will get us towards the target home location.
    return MoveTowards(board, r, c, closestRow, closestCol);
}

// Moves towards a target location, if possible.
Move Player::MoveTowards(const Board& board, int curR, int curC, int targetR, int targetC) {
    int dist = GetDistance(curR, curC, targetR, targetC);

    // Look at all neighbors.
    for (int i = -1; i <= 1; i++) {
        if (i == 0) {
            continue;
        }
        for (int j = -1; j <= 1; j++) {
            if (j == 0) {
                continue;
            }
            // Skip this straight away if it doesn't move us closer to the target.
            if (dist < GetDistance(curR + i, curC + j, targetR, targetC)) {
                continue;
            }

            // Get the neighboring piece. If we are off the board, skip it.
            Piece neighbor;
            try {
                neighbor = board.GetOccupant(curR + i, curC + j);
            }
            catch (exception) {
                continue;
            }
            // If this space is free, return a move to it.
            if (neighbor.IsEmpty()) {  
                return Move(curR, curC, GetDirection(i, j), Move::Help, Move::Advance);
            }
        }
    }
    // Return a null move if we cant get closer.
    return Move();
}

// Gets a cardinal direction based of of positive and negative offsets from a point.
Move::Direction Player::GetDirection(int rOffset, int cOffset) {
    if (rOffset < 0 && cOffset < 0) {
        return Move::NW;
    }
    else if (rOffset < 0 && cOffset > 0) {
        return Move::NE;
    }
    else if (rOffset > 0 && cOffset > 0) {
        return Move::SE;
    }
    else {
        return Move::SW;
    }
}