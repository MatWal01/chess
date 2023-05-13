#include "gameLogic.h"


Piece Position::getPiece(int row, int column)
{
    return pieces.at(column).at(row);
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
                    pieces.at(i).at(j).pieceSymbol = '\0';
                    j++;
                }
                break;
            default:
                pieces.at(i).at(j).pieceSymbol = temp;
                j++;
        }
        charCounter++;

    }

    return;
}


Position::Position(std::string FEN)
{
    // TODO: change setPosition fn and change 
    setPosition(FEN);
}


Position::Position()
{
    Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
