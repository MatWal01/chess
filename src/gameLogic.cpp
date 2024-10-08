#include <iostream>
#include "gameLogic.h"
#include "interface.h"


// TODO
bool Position::isInCheck()
{
    char tempKing {'\0'};
    char oppositeKing {'\0'};
    char oppositeQueen {'\0'};
    char oppositeRook {'\0'};
    char oppositeBishop {'\0'};
    char oppositeKnight {'\0'};

    if (onMove == 'W')
    {
        tempKing = 'K';
        oppositeKing = 'k';
        oppositeQueen = 'q';
        oppositeRook = 'r';
        oppositeBishop = 'b';
        oppositeKnight = 'n';
    }
    else
    {
        tempKing = 'k';
        oppositeKing = 'K';
        oppositeQueen = 'Q';
        oppositeRook = 'R';
        oppositeBishop = 'B';
        oppositeKnight = 'N';
    }

    piecePos kingPosition {-1, -1};
    piecePos oppositeKingPosition {-1, -1};

    // find King
    for (int rank {0}; rank < 8; rank++)
    {
        for (int file {0}; file < 8; file++)
        {
            if (pieces.at(rank).at(file) == tempKing)
            {
                kingPosition.rank = rank;
                kingPosition.file = file;
            }
            else if(pieces.at(rank).at(file) == oppositeKing)
            {
                oppositeKingPosition.rank = rank;
                oppositeKingPosition.file = file;
            }

        }
    }

    // no king on the board
    if (
        (kingPosition.rank < 0 || kingPosition.file < 0)
        ||
        (oppositeKingPosition.rank < 0 || oppositeKingPosition.file < 0)
        )
    {
        return false;
    }

    // check for queens
    // check for rooks
    char temp {'\0'};
    for (int rank {0}; rank < 8; rank++)
    {
        temp = pieces.at(rank).at(kingPosition.file);
        if (
            (temp == oppositeRook || temp == oppositeQueen)
            &&
            !invalidRookMove(kingPosition,{rank, kingPosition.file})
            )
        {
            return true;
        }
    }

    for (int file {0}; file < 8; file++)
    {
        temp = pieces.at(kingPosition.rank).at(file);
        if (
            (temp == oppositeRook || temp == oppositeQueen)
            &&
            !invalidRookMove(kingPosition,{kingPosition.rank, file})
            )
        {
            return true;
        }
    }


    // check for bishops
    for (int i {0}, j {0}; isInBoardBounds({kingPosition.rank + i, kingPosition.file + j}); i++, j++)
    {
        temp = pieces.at(kingPosition.rank + i).at(kingPosition.file + j);
        if (temp == oppositeBishop || temp == oppositeQueen)
        {
            if (!invalidDiagonalMove(kingPosition, {kingPosition.rank + i, kingPosition.file + j}))
            {
                return true;
            }
        }
    }

    for (int i {0}, j {0}; isInBoardBounds({kingPosition.rank + i, kingPosition.file + j}); i++, j--)
    {
        temp = pieces.at(kingPosition.rank + i).at(kingPosition.file + j);
        if (temp == oppositeBishop || temp == oppositeQueen)
        {
            if (!invalidDiagonalMove(kingPosition, {kingPosition.rank + i, kingPosition.file + j}))
            {
                return true;
            }
        }
    }

    for (int i {0}, j {0}; isInBoardBounds({kingPosition.rank + i, kingPosition.file + j}); i--, j++)
    {
        temp = pieces.at(kingPosition.rank + i).at(kingPosition.file + j);
        if (temp == oppositeBishop || temp == oppositeQueen)
        {
            if (!invalidDiagonalMove(kingPosition, {kingPosition.rank + i, kingPosition.file + j}))
            {
                return true;
            }
        }
    }

    for (int i {0}, j {0}; isInBoardBounds({kingPosition.rank + i, kingPosition.file + j}); i--, j--)
    {
        temp = pieces.at(kingPosition.rank + i).at(kingPosition.file + j);
        if (temp == oppositeBishop || temp == oppositeQueen)
        {
            if (!invalidDiagonalMove(kingPosition, {kingPosition.rank + i, kingPosition.file + j}))
            {
                return true;
            }
        }
    }

    // check for knights
    std::vector<piecePos> knightMoves;
    knightMoves.push_back({kingPosition.rank + 2, kingPosition.file + 1});
    knightMoves.push_back({kingPosition.rank + 2, kingPosition.file - 1});
    knightMoves.push_back({kingPosition.rank - 2, kingPosition.file + 1});
    knightMoves.push_back({kingPosition.rank - 2, kingPosition.file - 1});
    knightMoves.push_back({kingPosition.rank + 1, kingPosition.file + 2});
    knightMoves.push_back({kingPosition.rank + 1, kingPosition.file - 2});
    knightMoves.push_back({kingPosition.rank - 1, kingPosition.file + 2});
    knightMoves.push_back({kingPosition.rank - 1, kingPosition.file - 2});

    for (int i {0}; i < knightMoves.size(); i++)
    {
        if (isInBoardBounds(knightMoves.at(i)))
        {
            if (pieces.at(knightMoves.at(i).rank).at(knightMoves.at(i).file) == oppositeKnight)
            {
                return true;
            }
        }
    }

    // check for pawns
    // white side
    if (onMove == 'W')
    {
        if (isInBoardBounds({kingPosition.rank + 1, kingPosition.file + 1}))
        {
            if (pieces.at(kingPosition.rank + 1).at(kingPosition.file + 1) == 'p')
            {
                return true;
            }
        }

        if (isInBoardBounds({kingPosition.rank + 1, kingPosition.file - 1}))
        {
            if (pieces.at(kingPosition.rank + 1).at(kingPosition.file - 1) == 'p')
            {
                return true;
            }
        }        
    }
    // black side
    if (onMove == 'b')
    {
        if (isInBoardBounds({kingPosition.rank - 1, kingPosition.file + 1}))
        {
            if (pieces.at(kingPosition.rank - 1).at(kingPosition.file + 1) == 'P')
            {
                return true;
            }
        }

        if (isInBoardBounds({kingPosition.rank - 1, kingPosition.file - 1}))
        {
            if (pieces.at(kingPosition.rank - 1).at(kingPosition.file - 1) == 'P')
            {
                return true;
            }
        }        
    }

    // check for kings
    for (int i {-1}; i < 2; i++)
    {
        for (int j {-1}; j < 2; j++)
        {
            if (isInBoardBounds({kingPosition.rank + i, kingPosition.file + j}))
            {
                if (pieces.at(kingPosition.rank + i).at(kingPosition.file + j) == oppositeKing)
                {
                    return true;
                }
            }
        }
    }

    return false;
}


bool Position::isInCheck(piecePos curr, piecePos next)
{
    Position temp;
    for (int i {0}; i < 8; i++)
    {
        for (int j {0}; j < 8; j++)
        {
            temp.pieces.at(i).at(j) = pieces.at(i).at(j);
        }
    }

    // temp.setPosition(FEN);       // doesnt work

    temp.pieces.at(next.rank).at(next.file) = temp.pieces.at(curr.rank).at(curr.file);
    temp.pieces.at(curr.rank).at(curr.file) = '\0';
    temp.onMove = onMove;

    return temp.isInCheck();
}


bool Position::areLegalMovesLeft()
{
    for (int i {0}; i < 8; i++)
    {
        for (int j {0}; j < 8; j++)
        {
            if (islower(pieces.at(i).at(j)) == islower(onMove))
            {
                for (int rank {0}; rank < 8; rank++)
                {
                    for (int file {0}; file < 8; file++)
                    {
                        if (isProperPieceMove({i, j}, {rank, file}))
                        {
                            if (isMoveLegal({i, j}, {rank, file}))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}


bool Position::isProperPieceMove(piecePos curr, piecePos next)
{
    // check if any given rank/file is within the chessboard bounds
    if (!isInBoardBounds(curr))
    {
        return false;
    }
    else if (!isInBoardBounds(next))
    {
        return false;
    }

    char temp = pieces.at(curr.rank).at(curr.file);

    switch(temp)
    {
        case '\0':  // check if there is a piece
            return false;
        case 'p':
        {
            // check for captures
            if ((curr.file == next.file - 1 || curr.file == next.file + 1) && curr.rank == next.rank + 1)
            {
                // check if the next square is occupied by black piece
                if (isupper(pieces.at(next.rank).at(next.file)))
                {
                    return true;
                }
                // check for en passant
                // holy hell
                else
                {
                    return legalEnpassant(curr, next);
                }
            }

            if (pieces.at(next.rank).at(next.file) != '\0')
            {
                return false;
            }

            // check for first move (2 squares ahead)
            if ((curr.file == next.file && curr.rank == 6) && next.rank == 4)
            {
                return !invalidRookMove(curr, {4, curr.file});
            }
            // check for move 1 square ahead
            if (curr.file == next.file && curr.rank == next.rank + 1)
            {
                return true;
            }

            return false;
        }
        case 'P':
        {
            // check for captures
            if ((curr.file == next.file - 1 || curr.file == next.file + 1) && curr.rank == next.rank - 1)
            {
                // check if the next square is occupied by black piece
                if (islower(pieces.at(next.rank).at(next.file)))
                {
                    return true;
                }
                // check for en passant
                // holy hell
                else
                {
                    return legalEnpassant(curr, next);
                }
            }

            if (pieces.at(next.rank).at(next.file) != '\0')
            {
                return false;
            }

            // check for first move (2 squares ahead)
            if ((curr.file == next.file && curr.rank == 1) && next.rank == 3)
            {
                return !invalidRookMove(curr, {3, curr.file});
            }
            // check for move 1 square ahead
            if (curr.file == next.file && curr.rank == next.rank - 1)
            {
                return true;
            }

            return false;
        }
        case 'r':
        case 'R':
        {
            if (invalidRookMove(curr, next))
            {
                return false;
            }
            else
            {
                // losing castle rights
                // TODO: why tolower()???
                if (tolower(pieces.at(curr.rank).at(curr.file) == 'r'))
                {
                    if (curr.rank == 0 && curr.file == 0)
                    {
                        wQueenside = false;
                    }
                    else if (curr.rank == 0 && curr.file == 7)
                    {
                        wKingside = false;
                    }
                    else if (curr.rank == 7 && curr.file == 0)
                    {
                        bQueenside = false;
                    }
                    else if (curr.rank == 7 && curr.file == 7)
                    {
                        bKingside = false;
                    }
                }

                if (tolower(pieces.at(next.rank).at(next.file) == 'r'))
                {
                    if (next.rank == 0 && next.file == 0)
                    {
                        wQueenside = false;
                    }
                    else if (next.rank == 0 && next.file == 7)
                    {
                        wKingside = false;
                    }
                    else if (next.rank == 7 && next.file == 0)
                    {
                        bQueenside = false;
                    }
                    else if (next.rank == 7 && next.file == 7)
                    {
                        bKingside = false;
                    }
                }

                return true;
            }
        }
        case 'n':
        case 'N':
        {
            if (
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
                return true;
            }
            
            return false;
        }
        case 'b':
        case 'B':
        {
            if (invalidDiagonalMove(curr, next))
            {
                return false;
            }

            return true;
        }
        case 'q':
        case 'Q':
        {
            if (invalidRookMove(curr, next))
            {
                if (invalidDiagonalMove(curr, next))
                {
                    return false;
                }
            }
            return true;
        }
        case 'k':   // TODO: fix bug with black castle
        case 'K':
        {
            // check if the king will walk into a check

            // check if the square is 1 
            if (
                (curr.rank - next.rank <= 1 && curr.rank - next.rank >= -1)
                &&
                (curr.file - next.file <= 1 && curr.file - next.file >= -1)
                )
                {
                    return true;
                }

            // castle
            if (legalCastle(curr, next))
            {
                return true;
            }

            return false;
        }
    }

    std::cout << "this should never happen" << std::endl;
    return false;
}


bool Position::isInBoardBounds(piecePos curr)
{
    if (curr.rank > 7 || curr.rank < 0)
    {
        return false;
    }
    else if (curr.file > 7 || curr.file < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


bool Position::legalEnpassant(piecePos curr, piecePos next)
{
    char piece = pieces.at(curr.rank).at(curr.file);
    if (piece == 'p')
    {
        if (enpassant != "-")
        {
            piecePos enpassantPos {enpassant.at(1) - '1', enpassant.at(0) - 'a'};
            if (
                (enpassantPos.rank == next.rank && enpassantPos.file == next.file)
                &&
                (curr.rank == next.rank + 1 && (curr.file == next.file + 1 || curr.file == next.file - 1))
                )
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (enpassant != "-")
        {
            piecePos enpassantPos {enpassant.at(1) - '1', enpassant.at(0) - 'a'};
            if (
                (enpassantPos.rank == next.rank && enpassantPos.file == next.file)
                &&
                (curr.rank == next.rank - 1 && (curr.file == next.file + 1 || curr.file == next.file - 1))
                )
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    return false;
}


// check for obstacles (rook move) and a valid vertical/horizontal move
bool Position::invalidRookMove(piecePos curr, piecePos next)
{
    if (curr.rank == next.rank && curr.file == next.file) return true;
    if (curr.file == next.file)
    {
        if (curr.rank > next.rank)
        {
            for (int i = next.rank + 1; i < curr.rank; i++)
            {
                if (pieces.at(i).at(curr.file) != '\0')
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            for (int i = curr.rank + 1; i < next.rank; i++)
            {
                if (pieces.at(i).at(curr.file) != '\0')
                {
                    return true;
                }
            }
            return false;
        }
    }
    else if (curr.rank == next.rank)
    {
        if (curr.file > next.file)
        {
            for (int i = next.file + 1; i < curr.file; i++)
            {
                if (pieces.at(curr.rank).at(i) != '\0')
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            for (int i = curr.file + 1; i < next.file; i++)
            {
                if (pieces.at(curr.rank).at(i) != '\0')
                {
                    return true;
                }
            }
            return false;
        }
    }
    return true;
}


// check for obstacles (bishop move) and a valid diagonal
bool Position::invalidDiagonalMove(piecePos curr, piecePos next)
{
    int y {64};
    int x {-64};
    if (curr.rank == next.rank && curr.file == next.file) return true;

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
    
    if (curr.rank > next.rank)
    {
        if (curr.file > next.file)
        {
            for (int i {next.rank + 1}, j {next.file + 1}; i < curr.rank; i++, j++)
            {
                if (pieces.at(i).at(j) != '\0')
                {
                    return true;
                }
            }
        }
        else
        {
            for (int i {next.rank + 1}, j {next.file - 1}; i < curr.rank; i++, j--)
            {
                if (pieces.at(i).at(j) != '\0')
                {
                    return true;
                }
            }
        }
    }
    else
    {
        if (curr.file > next.file)
        {
            for (int i {next.rank - 1}, j {next.file + 1}; i > curr.rank; i--, j++)
            {
                if (pieces.at(i).at(j) != '\0')
                {
                    return true;
                }
            }
        }
        else
        {
            for (int i {next.rank - 1}, j {next.file - 1}; i > curr.rank; i--, j--)
            {
                if (pieces.at(i).at(j) != '\0')
                {
                    return true;
                }
            }
        }
    }

    return false;
}


bool Position::legalCastle(piecePos curr, piecePos next)
{
    char king = pieces.at(curr.rank).at(curr.file);

    if (isInCheck())
    {
        return false;
    }
    
    if (invalidRookMove(curr, next))
    {
        return false;
    }
    if (king == 'K')
    {
        if (curr.rank == 0 && next.rank == 0)
        {
            if (curr.file == next.file + 2 && wQueenside)
            {
                return true;
            }
            else if (curr.file == next.file - 2 && wKingside)
            {
                return true;
            }
        }
    }
    else if (king == 'k')
    {
        if (curr.rank == 7 && next.rank == 7)
        {
            if (curr.file == next.file + 2 && bQueenside)
            {
                return true;
            }
            else if (curr.file == next.file - 2 && bKingside)
            {
                return true;
            }
        }
    }

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


bool Position::isMoveLegal(piecePos curr, piecePos next)
{
    if (curr.rank == next.rank && curr.file == next.file)
    {
        return false;
    }

    // check if any given rank/file is within the chessboard bounds
    if (!isInBoardBounds(curr))
    {
        return false;
    }
    else if (!isInBoardBounds(next))
    {
        return false;
    }    

    // check if correct piece colour was chosen
    if (!(islower(onMove) == islower(pieces.at(curr.rank).at(curr.file))))
    {
        return false;
    }

    // check if the king could be captured in the next move (illegal)
    if (isInCheck(curr, next))
    {
        return false;
    }

    // check if the place you want move the piece to is occupied by your other piece
    if (pieces.at(next.rank).at(next.file) == '\0')
    {
        ;
    }
    else if (std::islower(pieces.at(curr.rank).at(curr.file)) == std::islower(pieces.at(next.rank).at(next.file)))
    {
        return false;
    }

    

    return isProperPieceMove(curr, next);
}


bool Position::movePiece(piecePos curr, piecePos next)
{
    if (this->next != nullptr)
    {
        return false;
    }

    char temp = pieces.at(curr.rank).at(curr.file);

    if (!isMoveLegal(curr, next))
    {
        return false;
    }

    moveNotation = moveToAlgebraicNotation(curr, next);

    // castle
    if (legalCastle(curr, next))
    {
        bool queenside {false};         // queenside == false => kingside castle
        if (curr.file == next.file + 2)
        {
            queenside = true;
        }

        if (queenside)
        {
            pieces.at(next.rank).at(next.file + 1) = pieces.at(next.rank).at(next.file - 2);
            pieces.at(next.rank).at(next.file - 2) = '\0';
        }
        else
        {
            pieces.at(next.rank).at(next.file - 1) = pieces.at(next.rank).at(next.file + 1);
            pieces.at(next.rank).at(next.file + 1) = '\0';
        }

        // set castle rights
        if (onMove == 'W')
        {
            wQueenside = false;
            wKingside = false;
        }
        else
        {
            bQueenside = false;
            bKingside = false;
        }
    }

    // losing castle rights
    if (temp == 'K')
    {
        wQueenside = false;
        wKingside = false;
    }
    else if (temp == 'k')
    {
        bQueenside = false;
        bKingside = false;
    }

    // enpassant
    if (onMove == 'W')
    {
        if (enpassant != "-")
        {
            piecePos enpassantPos {enpassant.at(1) - '1', enpassant.at(0) - 'a'};
            if (
                (enpassantPos.rank == next.rank && enpassantPos.file == next.file)
                &&
                (curr.rank == next.rank - 1 && (curr.file == next.file + 1 || curr.file == next.file - 1))
                )
            {
                pieces.at(enpassantPos.rank - 1).at(enpassantPos.file) = '\0';
            }
        }
    }
    else
    {
        if (enpassant != "-")
        {
            piecePos enpassantPos {enpassant.at(1) - '1', enpassant.at(0) - 'a'};
            if (
                (enpassantPos.rank == next.rank && enpassantPos.file == next.file)
                &&
                (curr.rank == next.rank + 1 && (curr.file == next.file + 1 || curr.file == next.file - 1))
                )
            {
                pieces.at(enpassantPos.rank + 1).at(enpassantPos.file) = '\0';
            }
        }
    }

    // note pawn move by 2 squares
    // TODO: note only if enpassant can happen in the next move
    enpassant.clear();
    if (tolower(temp) == 'p')
    {
        if (curr.rank - next.rank == -2)
        {
            enpassant.push_back('a' + curr.file);
            enpassant.push_back('3');
        }
        else if (curr.rank - next.rank == 2)
        {
            enpassant.push_back('a' + curr.file);
            enpassant.push_back('6');
        }
    }

    if (enpassant.empty())
    {
        enpassant = "-";
    }


    pieces.at(curr.rank).at(curr.file) ='\0';
    pieces.at(next.rank).at(next.file) = temp;

    if (onMove == 'W')
    {
        onMove = 'b';
    }
    else
    {
        onMove = 'W';
    }

    // promote to a queen
    if (temp == 'p' || temp =='P')
    {
        bool promotion {false};
        for (size_t i {0}; i < 8; i++)
        {
            if (pieces.at(0).at(i) == 'p')
            {
                pieces.at(0).at(i) = 'q';
                promotion = true;
            }
        }

        for (size_t i {0}; i < 8; i++)
        {
            if (pieces.at(7).at(i) == 'P')
            {
                pieces.at(7).at(i) = 'Q';
                promotion = true;
            }
        }

        if (promotion)
        {
            if (moveNotation.at(moveNotation.size() - 1) == '+')
            {
                moveNotation.pop_back();
                moveNotation += "=Q+";
            }
            else
            {
                moveNotation += "=Q";
            }
        }
    }

    if (!areLegalMovesLeft())
    {
        end = true;
        if (isInCheck())
        {
            moveNotation.pop_back();
            moveNotation += '#';
            if (onMove == 'W')
            {
                std::cout << "Black Wins" << std::endl;
            }
            else
            {
                std::cout << "White Wins" << std::endl;
            }
        }
        else
        {
            std::cout << "Stalemate!" << std::endl;
        }
    }

    std::cout << moveNotation << std::endl;
    FEN = returnFEN();
    return true;
}



Position::Position(std::string FEN)
{
    setPosition(FEN);
}

Position::Position()
{
    setPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
