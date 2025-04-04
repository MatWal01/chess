#include <iostream>
#include "gameLogic.h"
#include "interface.h"


bool PiecePos::isInBoardBounds()
{
    if (rank > 7 || rank < 0)
    {
        return false;
    }
    else if (file > 7 || file < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// returns a bitboard with a single piece on it
bitboard PiecePos::returnBitboard()
{
    bitboard temp {1};
    temp <<= (file) + (rank) * 8;
    return temp;
}


bool operator== (const PiecePos i, const PiecePos j)
{
    return (i.rank == j.rank && i.file == j.file);
}

// TODO
bool Position::isInCheck()
{
    // no king on the board
    if (
        !(pieces.at(static_cast<int>(Pieces::wKing)))
        ||
        !(pieces.at(static_cast<int>(Pieces::bKing)))
        )
    {
        return false;
    }

    // TODO:
    // create a new position as if you had not made a move
    // if your king can be taken you are in check 

    return false;
}


// bool Position::areLegalMovesLeft()
// {
//     for (int i {0}; i < 8; i++)
//     {
//         for (int j {0}; j < 8; j++)
//         {
//             if (islower(pieces.at(i).at(j)) == islower(onMove))
//             {
//                 for (int rank {0}; rank < 8; rank++)
//                 {
//                     for (int file {0}; file < 8; file++)
//                     {
//                         if (isProperPieceMove({i, j}, {rank, file}))
//                         {
//                             if (isMoveLegal({i, j}, {rank, file}))
//                             {
//                                 return true;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     return false;
// }


bool Position::invalidPawnMove(PiecePos curr, PiecePos next)
{
    if (curr.file != next.file)
    {
        return true;
    }

    return false;
}

// check for obstacles (rook move) and a valid vertical/horizontal move
bool Position::invalidRookMove(PiecePos curr, PiecePos next)
{
    if (curr.rank == next.rank || curr.file == next.file)
    {
        return false;
    }

    return true;
}

// assumes curr and next are valid
bool Position::invalidKnightMove(PiecePos curr, PiecePos next)
{
    // 8 knight moves
    if 
    (
        (
        ((curr.file == next.file + 2 && curr.rank == next.rank + 1) || (curr.file == next.file + 2 && curr.rank == next.rank - 1))
        ||
        ((curr.file == next.file - 2 && curr.rank == next.rank + 1) || (curr.file == next.file - 2 && curr.rank == next.rank - 1))
        )
        ||
        (
        ((curr.file == next.file + 1 && curr.rank == next.rank + 2) || (curr.file == next.file + 1 && curr.rank == next.rank - 2))
        ||
        ((curr.file == next.file - 1 && curr.rank == next.rank + 2) || (curr.file == next.file - 1 && curr.rank == next.rank - 2))
        )
    )
    {
        return false;
    }

    return true;
}

// check for obstacles (bishop move) and a valid diagonal
bool Position::invalidBishopMove(PiecePos curr, PiecePos next)
{
    int y {64};
    int x {-64};
    // if absolute values of (old.x - new.x) and (old.y - new.y) are equal then its a diagonal move
    if (curr.rank > next.rank)
    {
        y = curr.rank - next.rank;
    }
    else
    {
        y = next.rank - curr.rank;
    }

    if (curr.file > next.file)
    {
        x = curr.file - next.file;
    }
    else
    {
        x = next.file - curr.file;
    }

    if (x != y)
    {
        return true;
    }

    return false;
}


bool Position::invalidKingMove(PiecePos curr, PiecePos next)
{
    int i = curr.rank - next.rank;
    int j = curr.file - next.file;

    if (i > 1 || i < -1)
    {
        return true;
    }

    if (j > 1 || j < -1)
    {
        return true;
    }

    return false;
}


bool Position::legalCastle(PiecePos curr, PiecePos next)
{
    if (whiteOnMove)
    {
        if (!(wQueenside || wKingside))
        {
            return false;
        }
    }
    else
    {
        if (!(bQueenside || bKingside))
        {
            return false;
        }
    }
    
    if (isInCheck())
    {
        return false;
    }
    
    // if (invalidRookMove(curr, next))
    // {
    //     return false;
    // }
    // if (king == 'K')
    // {
    //     if (curr.rank == 0 && next.rank == 0)
    //     {
    //         if (curr.file == next.file + 2 && wQueenside)
    //         {
    //             return true;
    //         }
    //         else if (curr.file == next.file - 2 && wKingside)
    //         {
    //             return true;
    //         }
    //     }
    // }
    // else if (king == 'k')
    // {
    //     if (curr.rank == 7 && next.rank == 7)
    //     {
    //         if (curr.file == next.file + 2 && bQueenside)
    //         {
    //             return true;
    //         }
    //         else if (curr.file == next.file - 2 && bKingside)
    //         {
    //             return true;
    //         }
    //     }
    // }

    return false;
}


// check if the piece you want to move is pinned to their king
// redundant use isInCheck(next) instead; also unfinished
// kept just because stackoverflow sugested to use goto there (and in 2 other places on the same day)
// bool Position::isPinned(piecePos curr)
// {
//     // find their king
//     char temp = pieces.at(curr.rank).at(curr.file);

//     if (temp == 'k' || temp == 'K')
//     {
//         return false;
//     }

//     int kingRank {-1};
//     int kingFile {-1};

//     for (size_t rank {0}; rank < 8; rank++)
//     {
//         for (size_t file {0}; file < 8; file++)
//         {       
//             if (
//                 toupper(pieces.at(rank).at(file)) == 'K'
//                 &&
//                 isupper(pieces.at(rank).at(file)) == islower(temp)
//                 )
//                 {
//                     kingRank = rank;
//                     kingFile = file;
//                     // use goto from there lmao??
//                 }
//         }
//     }

//     // check if piece is on the same file/rank as their king
//     if (curr.rank - kingRank == 0)
//     {
        
//     }
//     else if (curr.file - kingFile == 0)
//     {

//     }

//     // check if piece is on the same diagonal as their king
//     bool sameDiagonal {false};
    

//     return false;
// }


bool Position::isMoveLegal(PiecePos curr, PiecePos next)
{
    // move to same place
    if (curr.rank == next.rank && curr.file == next.file)
    {
        return false;
    }

    // check if any given rank/file is within the chessboard bounds
    if (!curr.isInBoardBounds())
    {
        return false;
    }
    else if (!next.isInBoardBounds())
    {
        return false;
    }    

    bitboard currPiece = curr.returnBitboard();
    size_t indexCurr {0};
    for (; indexCurr < pieces.size(); indexCurr++)
    {
        if (currPiece & pieces.at(indexCurr))
        {
            break;
        }
    }
    
    // no pieces at selected square
    if (indexCurr == 12)
    {
        return false;
    }

    // check if correct piece colour was chosen
    if (indexCurr > static_cast<size_t>(Pieces::wKing) == whiteOnMove)
    {
        return false;
    }

    // check if it land on the same colour
    bitboard nextPiece = next.returnBitboard();
    size_t indexNext {0};
    for (; indexNext < pieces.size(); indexNext++)
    {
        if (nextPiece & pieces.at(indexNext))
        {
            break;
        }
    }
    
    // check if piece lands on another of the same colour
    // white
    if (indexCurr <= static_cast<size_t>(Pieces::wKing) && indexNext <= static_cast<size_t>(Pieces::wKing))
    {
        return false;
    }

    // black
    if (indexCurr > static_cast<size_t>(Pieces::wKing) && indexNext > static_cast<size_t>(Pieces::wKing))
    {
        // no piece at destination
        if (indexNext != 12)
        {
            return false;
        }
    }
    
    switch (indexCurr % 6)
    {
        case 0:
        return !invalidPawnMove(curr, next);
        case 1:
        return !invalidRookMove(curr, next);
        case 2:
        return !invalidKnightMove(curr, next);
        case 3:
        return !invalidBishopMove(curr,next);
        case 4:
        return (!invalidBishopMove(curr,next) || !invalidRookMove(curr, next));
        case 5:
        return (!invalidKingMove(curr, next) || legalCastle(curr, next));
        default:
        {
            std::cerr << "isMoveLegal(): should never happen - switch default\n";
            return false;
        }
    }
    
    // // check if the king could be captured in the next move (illegal)
    // if (isInCheck(curr, next))
    // {
    //     return false;
    // }

    std::cerr << "isMoveLegal(): should never happen - end\n";
    return false;
    // return isProperPieceMove(curr, next);
}

// calls isMoveLegal(), moves a piece, changes the castle rights and ensures the same side cannot move twice
bool Position::movePiece(PiecePos curr, PiecePos next)
{
    bitboard currPiece = curr.returnBitboard();
    size_t indexCurr {0};
    // find a selected type of piece
    for (; indexCurr < pieces.size(); indexCurr++)
    {
        if (currPiece & pieces.at(indexCurr))
        {
            break;
        }
    }
    
    if (!isMoveLegal(curr, next))
    {
        return false;
    }
    
    bitboard nextPiece = next.returnBitboard();
    size_t indexNext {0};
    // find a kind of a piece on a destination square
    for (; indexNext < pieces.size(); indexNext++)
    {
        if (nextPiece & pieces.at(indexNext))
        {
            // and take the piece
            pieces.at(indexNext) -= nextPiece;
            break;
        }
    }

    // remove picked piece from origin
    pieces.at(indexCurr) -= currPiece;

    // add selected piece
    pieces.at(indexCurr) += nextPiece;

    // castling rights
    switch (static_cast<Pieces>(indexCurr))
    {
        case Pieces::wRook:
        {
            if (curr.rank == 0)
            {
                if (curr.file == 0)
                {
                    wQueenside = false;
                }
                else if (curr.file == 7)
                {
                    wKingside = false;
                }
            }
            break;
        }
        case Pieces::wKing:
        {
            wQueenside = false;
            wKingside = false;
            break;
        }
        case Pieces::bRook:
        {
            if (curr.rank == 7)
            {
                if (curr.file == 0)
                {
                    wQueenside = false;
                }
                else if (curr.file == 7)
                {
                    wKingside = false;
                }
            }
            break;
        }
        case Pieces::bKing:
        {
            bQueenside = false;
            bKingside = false;
            break;
        }
    }

    // now the opposite side moves
    if (whiteOnMove)
    {
        whiteOnMove = false;
    }
    else
    {
        whiteOnMove = true;
    }

    return true;
}


// Position::Position(std::string FEN)
// {
//     setPosition(FEN);
// }


size_t binaryHammingWeight(bitboard in) // by Peter Wegner (1960)
{
    size_t count = 0;
    while (in) {
        count++;
        in &= in - 1; // reset LS1B
    }
    return count;
}


PiecePos bitboardToPiecePos(bitboard piece)
{
    if (binaryHammingWeight(piece) != 1)
    {
        return {-1, -1};
    }

    int j {1};
    for (bitboard i {1}; !(piece & i); i <<= 1)
    {
        j++;
    }

    return {(j / 8), (j % 8)};
}
