#include "gameLogic.h"
#include "interface.h"
#include <iostream>


bool Position::isMoveLegal(int pieceRank, int pieceFile, int newRank, int newFile)
{
    if (pieces.at(newRank).at(newFile) == '\0')
    {
        ;
    }
    else if (std::islower(pieces.at(pieceRank).at(pieceFile)) == std::islower(pieces.at(newRank).at(newFile)))
    {
        return false;
    }

    char temp = toupper(pieces.at(pieceRank).at(pieceFile));


    if (isPinned(pieceRank, pieceFile))
    {
        return false;
    }

    switch(temp)
    {
        case '\0':
            return false;
        default:
        case 'P':

        case 'R':

        case 'N':

        case 'B':

        case 'Q':

        case 'K':
            return true;
    }



    return true;
}

// check if the piece you want to move is pinned to their king
bool Position::isPinned(int pieceRank, int pieceFile)
{
    // find their king
    char temp = pieces.at(pieceRank).at(pieceFile);
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
    if (pieceRank - kingRank == 0)
    {
        
    }
    else if (pieceFile - kingFile == 0)
    {

    }

    // check if piece is on the same diagonal as their king
    bool sameDiagonal {false};


    // i bet you could optimize this
    

    return false;
}


bool Position::movePiece(int pieceRank, int pieceFile, int newRank, int newFile)
{
    if (!isMoveLegal(pieceRank, pieceFile, newRank, newFile))
    {
        return false;
    }

    char temp = pieces.at(pieceRank).at(pieceFile);
    pieces.at(pieceRank).at(pieceFile) ='\0';
    pieces.at(newRank).at(newFile) = temp;
    return true;
}


bool Position::isInCheck(int pieceRank, int pieceFile)
{
    bool isInCheck {false};
    char king = pieces.at(pieceRank).at(pieceFile);
    // check for Rooks/Queens
    // Ranks
    for (size_t j {0}; j < 8; j++)
    {
        char temp = pieces.at(pieceRank).at(j);
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
        char temp = pieces.at(pieceRank).at(j);
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
        char temp = pieces.at(i).at(pieceFile);
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
        char temp = pieces.at(i).at(pieceFile);
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


void Position::drawPosition(sf::RenderWindow* window, GameGraphics* ui)
{
    window->draw(ui->chessboard);
    for (int i {7}; i >= 0; i--)
        {
            for (size_t j {0}; j < 8; j++)
            {
                char temp = pieces.at(j).at(i);
                if (temp == '\0')
                {
                    continue;
                }
                sf::Sprite tempDraw = ui->returnSprite(temp);
                tempDraw.move(ui->pieceSize * i, ui->pieceSize * (7 - j));
                window->draw(tempDraw);
            }
        }
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


Position::Position()
{
    Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
