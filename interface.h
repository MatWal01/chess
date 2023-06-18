#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "gameLogic.h"
#ifndef _INTERFACE_H_
#define _INTERFACE_H_


class GameGraphics
{
private:
    sf::Texture chessboardTexture;

    // textures
    // white pieces
    sf::Texture whitePawnTexture;
    sf::Texture whiteRookTexture;
    sf::Texture whiteKnightTexture;
    sf::Texture whiteBishopTexture;
    sf::Texture whiteQueenTexture;
    sf::Texture whiteKingTexture;

    // black pieces
    sf::Texture blackPawnTexture;
    sf::Texture blackRookTexture;
    sf::Texture blackKnightTexture;
    sf::Texture blackBishopTexture;
    sf::Texture blackQueenTexture;
    sf::Texture blackKingTexture;

public:    
    // sprites
    sf::Sprite chessboard;

    // white pieces
    sf::Sprite whitePawn;
    sf::Sprite whiteRook;
    sf::Sprite whiteKnight;
    sf::Sprite whiteBishop;
    sf::Sprite whiteQueen;
    sf::Sprite whiteKing;

    // black pieces
    sf::Sprite blackPawn;
    sf::Sprite blackRook;
    sf::Sprite blackKnight;
    sf::Sprite blackBishop;
    sf::Sprite blackQueen;
    sf::Sprite blackKing;

    // size of chessboard and piece rectangles
    // set by setScale()
    float chessboardSize;
    float pieceSize; // should always be 1/8 of chessboard;

    const int WHEIGHT {800};
    const int WWIDTH {800};
    const sf::FloatRect board {0.f, 0.f, 800.f, 800.f};

    void drawChessboard(sf::RenderWindow* window);
    void drawPosition(sf::RenderWindow* window, Position* pos);
    sf::Sprite returnSprite(char piece);
    sf::Sprite* shareSprite(char temp);
    bool loadGameTextures();
    void setTextures();
    void setScale();
    GameGraphics();
};



#endif