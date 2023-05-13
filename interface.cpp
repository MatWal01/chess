#include <iostream>
#include "interface.h"
#include "gameLogic.h"


sf::Sprite GameGraphics::returnSprite(Piece piece)
{
    char temp = piece.pieceSymbol;
    switch (temp)
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

