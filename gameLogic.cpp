#include "gameLogic.h"
#include "interface.h"
#include <iostream>


bool Position::isMoveLegal(piecePos curr, piecePos next)
{
    // check if any given rank/file is within the chessboard bounds
    if (curr.rank > 7 || curr.rank < 0)
    {
        return false;
    }
    else if (curr.file > 7 || curr.file < 0)
    {
        return false;
    }
    else if (next.rank > 7 || next.rank < 0)
    {
        return false;
    }
    else if (next.file > 7 || next.file < 0)
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

    // // check if the piece you want to move is pinned to your king
    // if (isPinned(curr))
    // {
    //     return false;
    // }

    // if (onMove == 'w')
    // {
    //             switch(temp)
    //     {
    //         case '\0':
    //             return false;
    //         default:
    //         case 'P':
    //         {
    //             // check for captures
    //             if (islower(pieces.at(next.rank).at(curr.file)) && pieces.at(next.rank).at(curr.file) != '\0')
    //             {
    //                 if (next.rank - curr.rank != -1) // not sure if i should use -1 or 1 lmao
    //                 {
    //                     return false;
    //                 }

    //                 if (!(next.file - curr.file == 1 || next.file - curr.file == -1))
    //                 {
    //                     return false;
    //                 }
    //             }
    //             // check for en passant

    //             // check for first move (2 squares ahead)

    //             // check for move 1 square ahead
                    
    //         }
    //         case 'R':
            
    //         case 'N':

    //         case 'B':

    //         case 'Q':

    //         case 'K':
    //             return true;
    //     }
    // }
    // else
    // {
    //     switch(temp)
    //     {
    //         case '\0':
    //             return false;
    //         default:
    //         case 'p':
    //         {
    //             // check for captures
    //             if (islower(pieces.at(next.rank).at(curr.file)) && pieces.at(next.rank).at(curr.file) != '\0')
    //             {
    //                 if (next.rank - curr.rank != -1) // not sure if i should use -1 or 1 lmao
    //                 {
    //                     return false;
    //                 }

    //                 if (!(next.file - curr.file == 1 || next.file - curr.file == -1))
    //                 {
    //                     return false;
    //                 }
    //             }
    //             // check for en passant

    //             // check for first move (2 squares ahead)

    //             // check for move 1 square ahead
                    
    //         }
    //         case 'r':

    //         case 'n':

    //         case 'b':

    //         case 'q':

    //         case 'k':
    //             return true;
    //     }

    // }

    return true;
}

// check if the piece you want to move is pinned to their king
bool Position::isPinned(piecePos curr)
{
    // find their king
    char temp = pieces.at(curr.rank).at(curr.file);
    int kingRank {-1};
    int kingFile {-1};

    for (size_t rank {0}; rank < 8; rank++)
    {
        for (size_t file {0}; file < 8; file++)
        {       
            if (
                toupper(pieces.at(rank).at(file)) == 'K'
                &&
                isupper(pieces.at(rank).at(file)) == islower(temp)
                )
                {
                    kingRank = rank;
                    kingFile = file;
                    // use goto from there lmao??
                }
        }
    }

    // check if piece is on the same file/rank as their king
    if (curr.rank - kingRank == 0)
    {
        
    }
    else if (curr.file - kingFile == 0)
    {

    }

    // check if piece is on the same diagonal as their king
    bool sameDiagonal {false};


    // i bet you could optimize this
    

    return false;
}


bool Position::movePiece(piecePos curr, piecePos next)
{
    if (!isMoveLegal(curr, next))
    {
        return false;
    }

    char temp = pieces.at(curr.rank).at(curr.file);
    pieces.at(curr.rank).at(curr.file) ='\0';
    pieces.at(next.rank).at(next.file) = temp;
    return true;
}


bool Position::isInCheck(piecePos curr)
{
    bool isInCheck {false};
    char king = pieces.at(curr.rank).at(curr.file);
    // check for Rooks/Queens
    // Ranks
    for (size_t j {0}; j < 8; j++)
    {
        char temp = pieces.at(curr.rank).at(j);
        if (king = temp)
        {
            break;
        }
        
        switch (temp)
        {
            case '\0':
                continue;
            case 'R':
            case 'Q':
            {
                if (islower(king))
                {
                    isInCheck = true;
                }
                else
                {
                    isInCheck = false;
                }
                break;
            }
            case 'r':
            case 'q':
            {
                if (isupper(king))
                {
                    isInCheck = true;
                }
                else
                {
                    isInCheck = false;
                }
                break;
            }
            default:
            {
                isInCheck = false;
                break;
            }
        }
    }

    if (isInCheck)
    {
        return true;
    }

    for (int j {7}; j >= 0; j--)
    {
        char temp = pieces.at(curr.rank).at(j);
        if (king = temp)
        {
            break;
        }
        
        switch (temp)
        {
            case '\0':
                continue;
            case 'R':
            case 'Q':
            {
                if (islower(king))
                {
                    isInCheck = true;
                }
                else
                {
                    isInCheck = false;
                }
                break;
            }
            case 'r':
            case 'q':
            {
                if (isupper(king))
                {
                    isInCheck = true;
                }
                else
                {
                    isInCheck = false;
                }
                break;
            }
            default:
            {
                isInCheck = false;
                break;
            }
        }
    }

    if (isInCheck)
    {
        return true;
    }

    // Files
    for (size_t i {0}; i < 8; i++)
    {
        char temp = pieces.at(i).at(curr.file);
        if (king = temp)
        {
            break;
        }
        
        switch (temp)
        {
            case '\0':
                continue;
            case 'R':
            case 'Q':
            {
                if (islower(king))
                {
                    isInCheck = true;
                }
                else
                {
                    isInCheck = false;
                }
                break;
            }
            case 'r':
            case 'q':
            {
                if (isupper(king))
                {
                    isInCheck = true;
                }
                else
                {
                    isInCheck = false;
                }
                break;
            }
            default:
            {
                isInCheck = false;
                break;
            }
        }
    }

    if (isInCheck)
    {
        return true;
    }

    for (int i {7}; i >= 0; i--)
    {
        char temp = pieces.at(i).at(curr.file);
        if (king = temp)
        {
            break;
        }
        
        switch (temp)
        {
            case '\0':
                continue;
            case 'R':
            case 'Q':
            {
                if (islower(king))
                {
                    isInCheck = true;
                }
                else
                {
                    isInCheck = false;
                }
                break;
            }
            case 'r':
            case 'q':
            {
                if (isupper(king))
                {
                    isInCheck = true;
                }
                else
                {
                    isInCheck = false;
                }
                break;
            }
            default:
            {
                isInCheck = false;
                break;
            }
        }
    }

    if (isInCheck)
    {
        return true;
    }

    // check for Bishops/Queens

    // check for Knights
    // 8 is max places from which the knight can attack
    


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


    int charCounter {0};
    int i {7};
    int j {0};
    char temp;
    
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
