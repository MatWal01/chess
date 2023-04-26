#include <iostream>
#include "interface.h"

// ???
sf::Sprite GameGraphics::returnSprite(char piece)
{
    switch (piece)
    {        
        // white pieces
        case 'P':
            return whitePawn;
        case 'R':
            return whiteRook;
        case 'N':
            return whiteKnight;
        case 'B':
            return whiteBishop;
        case 'Q':
            return whiteQueen;
        case 'K':
            return whiteKing;
        
        // black pieces
        case 'p':
            return blackPawn;
        case 'r':
            return blackRook;
        case 'n':
            return blackKnight;
        case 'b':
            return blackBishop;
        case 'q':
            return blackQueen;
        case 'k':
            return blackKing;
        
        // no piece
        case '\0':  // should be unreachable
            return whiteKing;
        default:
            return blackKing;

    }
}


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

    whitePawnTexture.setSmooth(true);
    whiteRookTexture.setSmooth(true);
    whiteKnightTexture.setSmooth(true);
    whiteBishopTexture.setSmooth(true);
    whiteQueenTexture.setSmooth(true);
    whiteKingTexture.setSmooth(true);
    
    blackPawnTexture.setSmooth(true);
    blackRookTexture.setSmooth(true);
    blackKnightTexture.setSmooth(true);
    blackBishopTexture.setSmooth(true);
    blackQueenTexture.setSmooth(true);
    blackKingTexture.setSmooth(true);

    chessboard.setTexture(chessboardTexture);

    whitePawn.setTexture(whitePawnTexture);
    whiteRook.setTexture(whiteRookTexture);
    whiteKnight.setTexture(whiteKnightTexture);
    whiteBishop.setTexture(whiteBishopTexture);
    whiteQueen.setTexture(whiteQueenTexture);
    whiteKing.setTexture(whiteKingTexture);
    
    blackPawn.setTexture(blackPawnTexture);
    blackRook.setTexture(blackRookTexture);
    blackKnight.setTexture(blackKnightTexture);
    blackBishop.setTexture(blackBishopTexture);
    blackQueen.setTexture(blackQueenTexture);
    blackKing.setTexture(blackKingTexture);
}


void GameGraphics::setScale()
{
    sf::FloatRect board = chessboard.getGlobalBounds();
    // I assume all pieces files have the same resolution and are squares
    sf::FloatRect piece = blackRook.getGlobalBounds();
    chessboardSize = board.width;
    float scale = (board.width / 8.0) / piece.width;
    // hopefully all pieces are the same
    pieceSize = piece.width * scale;

    whitePawn.setScale(scale, scale);
    whiteRook.setScale(scale, scale);
    whiteKnight.setScale(scale, scale);
    whiteBishop.setScale(scale, scale);
    whiteQueen.setScale(scale, scale);
    whiteKing.setScale(scale, scale);
    
    blackPawn.setScale(scale, scale);
    blackRook.setScale(scale, scale);
    blackKnight.setScale(scale, scale);
    blackBishop.setScale(scale, scale);
    blackQueen.setScale(scale, scale);
    blackKing.setScale(scale, scale);
}


GameGraphics::GameGraphics()
{
    if (!loadGameTextures())
    {
        std::cout << "Unable to load textures" << std::endl;
        return;
    }
    setTexture();
    setScale();
    return;
}


char Position::getPiece(int row, int column)
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

