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

    sf::CircleShape legalMove;
    bool legalMoves[8][8] {false};  //[rank][file]
    float circleOffset {0};
    
    sf::RectangleShape picked;
    sf::RectangleShape checkmate;

    sf::Vector2i mouse;
    sf::Vector2f mouseF;
    
    bool firstClick {false};
    bool secondClick {false};
    piecePos firstPos {0, 0};
    piecePos secondPos {0, 0};

    // size of chessboard and piece rectangles
    // set by setScale()
    float chessboardSize;
    float pieceSize; // should always be 1/8 of chessboard;

    const int WHEIGHT {800};
    const int WWIDTH {800};
    const sf::FloatRect board {0.f, 0.f, 800.f, 800.f};

    void leftMouseInteract(sf::RenderWindow* const window, Position* const curr);
    void resetPicked();
    void drawChessboard(sf::RenderWindow* const window);
    void drawPosition(sf::RenderWindow* const window, Position* const pos);
    void getLegalMoves(Position* const pos);
    void resetLegalMoves();
    void drawLegalMoves(sf::RenderWindow* const window, Position* const pos);
    sf::Sprite returnSprite(char piece);
    sf::Sprite* shareSprite(char temp);
    bool loadGameTextures();
    void setTextures();
    void setScale();
    GameGraphics();
};



#endif