#include <iostream>
#include "gameLogic.h"


std::string Position::moveToAlgebraicNotation(piecePos curr, piecePos next)
{
    std::string notation {""};

    // // if illegal return empty string
    if (!isMoveLegal(curr, next))
    {
        return notation;
    }

    char piece = toupper(pieces.at(curr.rank).at(curr.file));
    bool destEmpty {pieces.at(next.rank).at(next.file) == '\0'};
    bool enpassant {legalEnpassant(curr, next)};

    switch (piece)
    {
        case 'P':
        {
            break;
        }
        case 'K':
        {
            if (legalCastle(curr, next))
            {
                if (curr.file - next.file > 0)
                {
                    notation = "O-O-O";
                }
                else
                {
                    notation = "O-O";
                }
                return notation;
            }
        }
        default:
        {
            notation += piece;
        }
    }

    // TODO: origin of piece if move is ambiguous

    if (!destEmpty || enpassant)
    {
        if (piece == 'P')
        {
            notation += ('a' + curr.file);
        }
        notation += 'x';
    }

    notation += ('a' + next.file);
    notation += ('1' + next.rank);

    Position temp;
    for (int i {0}; i < 8; i++)
    {
        for (int j {0}; j < 8; j++)
        {
            temp.pieces.at(i).at(j) = pieces.at(i).at(j);
        }
    }

    temp.pieces.at(next.rank).at(next.file) = temp.pieces.at(curr.rank).at(curr.file);
    temp.pieces.at(curr.rank).at(curr.file) = '\0';
    if (onMove == 'W')
    {
        temp.onMove = 'b';
    }
    else
    {
        temp.onMove = 'W';
    }

    if (temp.isInCheck())
    {
        notation += '+';
    }


    return notation;
}


std::string Position::returnFEN()
{
    char emptySquares {'0'};

    FEN.clear();
    for (int rank {7}; rank >= 0; rank--)
    {
        for (size_t file {0}; file < 8; file++)
        {
            if (pieces.at(rank).at(file) != '\0')
            {
                if (emptySquares != '0')
                {
                    FEN.push_back(emptySquares);
                    emptySquares = '0';
                }
                FEN.push_back(pieces.at(rank).at(file));
            }
            else
            {
                emptySquares++;
            }
        }
        if (emptySquares != '0')
        {
            FEN.push_back(emptySquares);
        }

        FEN.push_back('/');

        emptySquares = '0';
    }

    FEN.pop_back();         // remove last '/'
    FEN += ' ';

    FEN += tolower(tolower(onMove));
    FEN += ' ';

    bool noCastle {true};

    if (wKingside)
    {
        FEN += 'K';
        noCastle = false;
    }

    if (wQueenside)
    {
        FEN += 'Q';
        noCastle = false;
    }

    if (bKingside)
    {
        FEN += 'k';
        noCastle = false;
    }

    if (bQueenside)
    {
        FEN += 'q';
        noCastle = false;
    }

    if (noCastle)
    {
        FEN += '-';
    }

    FEN += ' ';

    FEN += enpassant;

    return FEN;
}


// sets a position 2D vector of chars from FEN
void Position::setPosition(std::string FEN)
{
    this->FEN = FEN;

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

    charCounter += 2;

    while (FEN.at(charCounter) != ' ')
    {
        if (FEN.at(charCounter) == '-')
        {
            wKingside = false;
            wQueenside = false;
            bKingside = false;
            bQueenside = false;
            charCounter++;
            break;
        }

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
    // enpassant move
    if (FEN.at(charCounter) != '-')
    {
        enpassant.at(0) = FEN.at(charCounter);
        enpassant += FEN.at(charCounter + 1);

        charCounter++;
    }
    charCounter++;
    // TODO: halfmoves counter

}