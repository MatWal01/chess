#pragma once
#include <vector>
#include <array>
#include <string>

#include <SFML/Graphics.hpp>
#include "gameLogic.h"


class Interface;

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
    float circleOffset {0};
    
    sf::RectangleShape picked;
    sf::RectangleShape checkmate;

    // size of chessboard and piece rectangles
    // set by setScale()
    float chessboardSize;
    float pieceSize; // should always be 1/8 of chessboard;

    const unsigned int WHEIGHT {800};
    const unsigned int WWIDTH {800};
    const sf::FloatRect board {0.f, 0.f, 800.f, 800.f};
    
    void drawPosition(sf::RenderWindow* const window, Position* const pos);
    void drawLegalMoves(sf::RenderWindow* const window, Interface* const ui);
    sf::Sprite returnSprite(size_t piece);
    sf::Sprite* shareSprite(size_t temp);
    bool loadGameTextures();
    void setTextures();
    void setScale();
    GameGraphics();
};

class Interface
{
private:
    sf::Vector2f mouseF;
    
    bool firstClick {false};
    bool secondClick {false};
    PiecePos firstPos {0, 0};
    PiecePos secondPos {0, 0};
public:
    bitboard legalMoves {0};
    sf::Vector2i mouse;
    
    void leftMouseInteract(sf::RenderWindow* const window, Position* const curr, GameGraphics* const g);
    void getLegalMoves(Position* const pos);
    void resetLegalMoves();
    void resetPicked(GameGraphics* const g);
};
