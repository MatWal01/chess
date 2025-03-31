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


bool Position::isProperPieceMove(PiecePos picked, PiecePos target)
{
    // check if any given rank/file is within the chessboard bounds
    if (!picked.isInBoardBounds())
    {
        return false;
    }
    else if (!target.isInBoardBounds())
    {
        return false;
    }

    size_t pickedIndex {0};
    if (onMove == 'B')
    {
        pickedIndex = 6;
    }

    bitboard pickedPiece = picked.returnBitboard();

    for (size_t i {0}; i < 6; i++, pickedIndex++)
    {
        if (pickedPiece & pieces.at(pickedIndex))
        {
            break;
        }
    }

    // no pieces at picked square
    if ((pickedIndex == 12 && onMove == 'B') || (pickedIndex == 6 && (onMove == 'W')))
    {
        return false;
    }

    return false;
}


bool Position::legalEnpassant(PiecePos curr, PiecePos next)
{
    // char piece = pieces.at(curr.rank).at(curr.file);
    // if (piece == 'p')
    // {
    //     if (enpassant != "-")
    //     {
    //         piecePos enpassantPos {enpassant.at(1) - '1', enpassant.at(0) - 'a'};
    //         if (
    //             (enpassantPos.rank == next.rank && enpassantPos.file == next.file)
    //             &&
    //             (curr.rank == next.rank + 1 && (curr.file == next.file + 1 || curr.file == next.file - 1))
    //             )
    //         {
    //             return true;
    //         }
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }
    // else
    // {
    //     if (enpassant != "-")
    //     {
    //         piecePos enpassantPos {enpassant.at(1) - '1', enpassant.at(0) - 'a'};
    //         if (
    //             (enpassantPos.rank == next.rank && enpassantPos.file == next.file)
    //             &&
    //             (curr.rank == next.rank - 1 && (curr.file == next.file + 1 || curr.file == next.file - 1))
    //             )
    //         {
    //             return true;
    //         }
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }

    return false;
}


// check for obstacles (rook move) and a valid vertical/horizontal move
bool Position::invalidRookMove(PiecePos curr, PiecePos next)
{
    return false;
    // if (curr.rank == next.rank && curr.file == next.file) return true;
    // if (curr.file == next.file)
    // {
    //     if (curr.rank > next.rank)
    //     {
    //         for (int i = next.rank + 1; i < curr.rank; i++)
    //         {
    //             if (pieces.at(i).at(curr.file) != '\0')
    //             {
    //                 return true;
    //             }
    //         }
    //         return false;
    //     }
    //     else
    //     {
    //         for (int i = curr.rank + 1; i < next.rank; i++)
    //         {
    //             if (pieces.at(i).at(curr.file) != '\0')
    //             {
    //                 return true;
    //             }
    //         }
    //         return false;
    //     }
    // }
    // else if (curr.rank == next.rank)
    // {
    //     if (curr.file > next.file)
    //     {
    //         for (int i = next.file + 1; i < curr.file; i++)
    //         {
    //             if (pieces.at(curr.rank).at(i) != '\0')
    //             {
    //                 return true;
    //             }
    //         }
    //         return false;
    //     }
    //     else
    //     {
    //         for (int i = curr.file + 1; i < next.file; i++)
    //         {
    //             if (pieces.at(curr.rank).at(i) != '\0')
    //             {
    //                 return true;
    //             }
    //         }
    //         return false;
    //     }
    // }
    // return true;
}


// check for obstacles (bishop move) and a valid diagonal
bool Position::invalidBishopMove(PiecePos curr, PiecePos next)
{
    // if absolute values of (old.x - new.x) and (old.y - new.y) are equal then its a diagonal move

    return false;
}


bool Position::legalCastle(PiecePos curr, PiecePos next)
{
    // char king = pieces.at(curr.rank).at(curr.file);

    // if (isInCheck())
    // {
    //     return false;
    // }
    
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

    // // check if any given rank/file is within the chessboard bounds
    // if (!isInBoardBounds(curr))
    // {
    //     return false;
    // }
    // else if (!isInBoardBounds(next))
    // {
    //     return false;
    // }    

    // // check if correct piece colour was chosen
    // if (!(islower(onMove) == islower(pieces.at(curr.rank).at(curr.file))))
    // {
    //     return false;
    // }

    // // check if the king could be captured in the next move (illegal)
    // if (isInCheck(curr, next))
    // {
    //     return false;
    // }

    // // check if the place you want move the piece to is occupied by your other piece
    // if (pieces.at(next.rank).at(next.file) == '\0')
    // {
    //     ;
    // }
    // else if (std::islower(pieces.at(curr.rank).at(curr.file)) == std::islower(pieces.at(next.rank).at(next.file)))
    // {
    //     return false;
    // }

    
    return true;
    // return isProperPieceMove(curr, next);
}


bool Position::movePiece(PiecePos curr, PiecePos next)
{
    std::cout << curr.file << curr.rank << '\n';
    std::cout << next.file << next.rank << std::endl;
    // check if the move already happened (past position is drawn)
    if (this->next != nullptr)
    {
        return false;
    }

    // if (!isMoveLegal(curr, next))
    // {
    //     return false;
    // }

    // check if selected square has piece on it
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
        std::cerr << "no pieces at selected square" << std::endl;
        return false;
    }

    pieces.at(indexCurr) -= currPiece;

    bitboard nextPiece {1};
    nextPiece <<= (next.file) + (next.rank) * 8;
    size_t indexNext {0};
    for (; indexNext < pieces.size(); indexNext++)
    {
        if (nextPiece & pieces.at(indexNext))
        {
            pieces.at(indexNext) -= nextPiece;
            break;
        }
    }
    // add selected piece
    pieces.at(indexCurr) += nextPiece;
    return true;
}



// Position::Position(std::string FEN)
// {
//     setPosition(FEN);
// }

// Position::Position()
// {
//     ;
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
