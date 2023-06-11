#include <iostream>
#include "interface.h"
#include "gameLogic.h"


void GameGraphics::drawChessboard(sf::RenderWindow* window)
{
    window->draw(chessboard);
}


void GameGraphics::drawPosition(sf::RenderWindow* window, Position* pos)
{
    
    for (int i {7}; i >= 0; i--)
        {
            for (size_t j {0}; j < 8; j++)
            {
                char temp = pos->pieces.at(j).at(i);
                if (temp == '\0')
                {
                    continue;
                }
                sf::Sprite tempDraw = returnSprite(temp);
                tempDraw.move(pieceSize * i, pieceSize * (7 - j));
                window->draw(tempDraw);
            }
        }
}


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
        case '\0':
            return whiteKing;
        default:
            return blackKing;

    }
}


sf::Sprite* GameGraphics::shareSprite(char temp)
{
    switch (temp)
    {        
        // white pieces
        case 'P':
            return &whitePawn;
        case 'R':
            return &whiteRook;
        case 'N':
            return &whiteKnight;
        case 'B':
            return &whiteBishop;
        case 'Q':
            return &whiteQueen;
        case 'K':
            return &whiteKing;
        
        // black pieces
        case 'p':
            return &blackPawn;
        case 'r':
            return &blackRook;
        case 'n':
            return &blackKnight;
        case 'b':
            return &blackBishop;
        case 'q':
            return &blackQueen;
        case 'k':
            return &blackKing;
        
        // no piece
        case '\0':
            return &whiteKing;
        default:
            return &blackKing;

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


void GameGraphics::setTextures()
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
    setTextures();
    setScale();
    return;
}
