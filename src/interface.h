#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <string>
#include "gameLogic.h"
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

enum PiecesInArray
{
    wPawn = 0,
    wRook,
    wKnight,
    wBishop,
    wQueen,
    wKing,
    bPawn,
    bRook,
    bKnight,
    bBishop,
    bQueen,
    bKing
};


class GameGraphics
{
private:
    sf::Texture chessboardTexture;

    // textures
    std::array<sf::Texture, 12> piecesTextures;

public:    
    // sprites
    sf::Sprite chessboard;
    std::array<sf::Sprite, 12> piecesSprites;

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

    const unsigned int WHEIGHT {800};
    const unsigned int WWIDTH {800};
    const sf::FloatRect board {0.f, 0.f, 800.f, 800.f};

    void leftMouseInteract(sf::RenderWindow* const window, Position* const curr);
    void resetPicked();
    void drawPosition(sf::RenderWindow* const window, Position* const pos);
    void getLegalMoves(Position* const pos);
    void resetLegalMoves();
    void drawLegalMoves(sf::RenderWindow* const window, Position* const pos);
    sf::Sprite returnSprite(char temp);
    sf::Sprite* shareSprite(char temp);
    bool loadGameTextures();
    void setTextures();
    void setScale();
    GameGraphics();
};



#endif