#include <iostream>
#include "gameLogic.h"
#include "interface.h"


bool Position::isMoveLegal(piecePos curr, piecePos next)
{
    // check if correct piece colour was chosen
    if (!(islower(onMove) == islower(pieces.at(curr.rank).at(curr.file))))
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

    // check if the king could be captured in the next move (illegal)
    if (isInCheck(next))
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
                else
                {
                    return false;
                }
            }

            if (pieces.at(next.rank).at(next.file) != '\0')
            {
                return false;
            }

            // check for en passant

            // check for first move (2 squares ahead)
            if ((curr.file == next.file && curr.rank == 6) && next.rank == 4)
            {
                return true;
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
                else
                {
                    return false;
                }
            }

            if (pieces.at(next.rank).at(next.file) != '\0')
            {
                return false;
            }

            // TODO
            // check for en passant
            // holy hell

            // check for first move (2 squares ahead)
            if ((curr.file == next.file && curr.rank == 1) && next.rank == 3)
            {
                return true;
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
        case 'k':
        case 'K':
        {
            // check if the king will walk into a check

            if (
                (curr.rank - next.rank <= 1 && curr.rank - next.rank >= -1)
                &&
                (curr.file - next.file <= 1 && curr.file - next.file >= -1)
                )
                {
                    return true;
                }

            // castle
            if (isInCheck(curr))
            {
                return false;
            }
            
            if (invalidRookMove(curr, next))
            {
                return false;
            }

            if (temp == 'K')
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
            else
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
            return false;
        }
    }

    std::cout << "this should never happen" << std::endl;
    return false;
}


// check if the piece you want to move is pinned to their king
// redundant use isInCheck(next) instead, also unfinished
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


// check for obstacles (rook move) and a valid vertical/horizontal move
bool Position::invalidRookMove(piecePos curr, piecePos next)
{
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


bool Position::movePiece(piecePos curr, piecePos next)
{
    char temp = pieces.at(curr.rank).at(curr.file);
    if (!isMoveLegal(curr, next))
    {
        std::cout << "illegal" << std::endl;
        return false;
    }

    if (temp == 'K')
    {
        if (curr.file == next.file + 2)
        {
            wQueenside = {false};
            wKingside = {false};
            pieces.at(next.rank).at(next.file + 1) = pieces.at(next.rank).at(next.file - 2);
            pieces.at(next.rank).at(next.file - 2) = '\0';

        }
        else if (curr.file == next.file - 2)
        {
            wQueenside = {false};
            wKingside = {false};
            pieces.at(next.rank).at(next.file - 1) = pieces.at(next.rank).at(next.file + 1);
            pieces.at(next.rank).at(next.file + 1) = '\0';
        }
        else
        {
            wQueenside = {false};
            wKingside = {false};
        }
    }

    if (temp == 'k')
    {
        if (curr.file == next.file + 2)
        {
            bQueenside = {false};
            bKingside = {false};
            pieces.at(next.rank).at(next.file + 1) = pieces.at(next.rank).at(next.file - 2);
            pieces.at(next.rank).at(next.file - 2) = '\0';

        }
        else if (curr.file == next.file - 2)
        {
            bQueenside = {false};
            bKingside = {false};
            pieces.at(next.rank).at(next.file - 1) = pieces.at(next.rank).at(next.file + 1);
            pieces.at(next.rank).at(next.file + 1) = '\0';
        }
        else
        {
            bQueenside = {false};
            bKingside = {false};
        }
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

    std::cout << "legal" << std::endl;
    return true;
}


bool Position::isInCheck(piecePos curr)
{
    bool isInCheck {false};

    // check for pawns
    if (onMove == 'W')
    {

    }
    else
    {

    }

    // check for queens (using funtions below)
    // check for rooks
    for (int i {0}; i < 8; i++)
    {
        if (onMove == 'W')
        {
            if (pieces.at(curr.rank).at(i) == 'r' || pieces.at(curr.rank).at(i) == 'q')
            {
                if (!invalidRookMove(curr, piecePos {curr.rank, i}))
                {
                    return true;
                }

                if (!invalidRookMove(curr, piecePos {i, curr.rank}))
                {
                    return true;
                }
            }
        }
        else
        {
            if (pieces.at(curr.rank).at(i) == 'r' || pieces.at(curr.rank).at(i) == 'q')
            {
                if (!invalidRookMove(curr, piecePos {curr.rank, i}))
                {
                    return true;
                }

                if (!invalidRookMove(curr, piecePos {i, curr.rank}))
                {
                    return true;
                }
            }
        }
    }


    // check for


    return false;
}


// sets a position 2D vector of chars from FEN
void Position::setPosition(std::string FEN)
{
    // turn pieces vector to 8x8 size
    pieces.resize(8);
    for (size_t i {0}; i < 8; i++)
    {
        pieces.at(i).resize(8);
    }


    size_t charCounter {0};
    int i {7};
    int j {0};
    char temp;
    
    // set pieces, skip '/' and numbers k times
    while (FEN.at(charCounter) != ' ')
    {
        temp = FEN.at(charCounter);
        if (temp - '0' > 0 && temp - '0' < 9)
        {
            temp = '0';
        }
        switch (temp)
        {
            case '/':
                i--;
                j = 0;
                break;
            case '0':
                for (int k {0}; k < FEN.at(charCounter) - '0'; k++)
                {
                    pieces.at(i).at(j) = '\0';
                    j++;
                }
                break;
            default:
                pieces.at(i).at(j) = temp;
                j++;
        }
        charCounter++;
    }
    // skip whitespace
    charCounter++;
    
    if (FEN.at(charCounter) == 'w')
    {
        onMove = 'W';
    }
    else
    {
        onMove = 'b';
    }
    charCounter + 2;

    if (FEN.at(charCounter) == '-')
    {
        wKingside = false;
        wQueenside = false;
        bKingside = false;
        bQueenside = false;
        charCounter++;
    }

    while (FEN.at(charCounter) != ' ')
    {
        if (FEN.at(charCounter) == 'K')
        {
            wKingside = true;
        }
        else if (FEN.at(charCounter) == 'Q')
        {
            wQueenside = true;
        }
        else if (FEN.at(charCounter) == 'k')
        {
            bKingside = true;
        }
        else if (FEN.at(charCounter) == 'q')
        {
            bQueenside = true;
        }

        charCounter++;
    }
    charCounter++;
    
    // TODO: enpassant move
    // TODO: halfmoves counter

    return;
}


Position::Position(std::string FEN)
{ 
    setPosition(FEN);
}

// Doesnt work lmao
Position::Position()
{
    Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
