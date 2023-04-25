#include "interface.h"

bool GameGraphics::loadGameTextures()
{
    if (!chessboardTexture.loadFromFile("textures/chessboard.png"))
    {
        return false;
    }
    // white pieces
    if (!whitePawnTexture.loadFromFile("textures/wPawn.png"))
    {
        return false;
    }
    if (!whiteRookTexture.loadFromFile("textures/wRook.png"))
    {
        return false;
    }
    if (!whiteKnightTexture.loadFromFile("textures/wKnight.png"))
    {
        return false;
    }
    if (!whiteBishopTexture.loadFromFile("textures/wBishop.png"))
    {
        return false;
    }
    if (!whiteQueenTexture.loadFromFile("textures/wQueen.png"))
    {
        return false;
    }
    if (!whiteKingTexture.loadFromFile("textures/wKing.png"))
    {
        return false;
    }

    // black pieces
    if (!blackPawnTexture.loadFromFile("textures/bPawn.png"))
    {
        return false;
    }
    if (!blackRookTexture.loadFromFile("textures/bRook.png"))
    {
        return false;
    }
    if (!blackKnightTexture.loadFromFile("textures/bKnight.png"))
    {
        return false;
    }
    if (!blackBishopTexture.loadFromFile("textures/bBishop.png"))
    {
        return false;
    }
    if (!blackQueenTexture.loadFromFile("textures/bQueen.png"))
    {
        return false;
    }
    if (!blackKingTexture.loadFromFile("textures/bKing.png"))
    {
        return false;
    }
    
    return true;
}

void GameGraphics::setTexture()
{
    chessboard.setTexture(chessboardTexture);

    whitePawn.setTexture(whitePawnTexture);
    whiteRook.setTexture(whiteRookTexture);
    whiteKnight.setTexture(whiteKnightTexture);
    whiteBishop.setTexture(whiteBishopTexture);
    whiteQueen.setTexture(whiteQueenTexture);
    whiteKing.setTexture(whiteKingTexture);
    
    blackRookTexture.setSmooth(true);
    blackPawn.setTexture(blackPawnTexture);
    blackRook.setTexture(blackRookTexture);
    blackKnight.setTexture(blackKnightTexture);
    blackBishop.setTexture(blackBishopTexture);
    blackQueen.setTexture(blackQueenTexture);
    blackKing.setTexture(blackKingTexture);
}


// TODO: change this function to void
std::vector<std::vector<char>> Position::setPosition(std::string FEN)
{
    std::vector<std::vector<char>> pieces;
    // turn pieces vector to 8x8 size
    pieces.resize(8);
    for (size_t i {0}; i < 8; i++)
    {
        pieces.at(i).resize(8);
    }

    int charCounter {0};
    while (charCounter < FEN.size())
    {
        for (int i {7}; FEN.at(charCounter) != ' ' && i >= 0; i--, charCounter++)
        {
            for (size_t j {0}; FEN.at(charCounter) != '/' && j < 8; j++)
            {
                char s = FEN.at(charCounter);
                // check if char is a number 1-8
                if (s - '0' > 0 && s - '0' < 9)
                {
                    s = '0';
                }

                switch (s)
                {
                    case '0': // if char is a digit
                        for (size_t k {0}; k < FEN.at(charCounter) - '0'; k++, j++)
                        {
                            pieces.at(i).at(j) = 0;
                        }
                        charCounter++;
                        break;
                    case '/':
                        j = 8;
                        break;
                    default:
                        pieces.at(i).at(j) = s;
                        charCounter++;
                        break;
                }
            }
        }
        break;                
    }

    return pieces;
}

Position::Position(std::string FEN)
{
    // TODO: change setPosition fn and change 
    pieces = setPosition(FEN);
}

Position::Position()
{
    Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

