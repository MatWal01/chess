#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

class Piece
{
public:
    char pieceSymbol {'\0'};
    sf::Sprite pieceSprite;

    char returnColor();
};

class Position
{
private:
    char onMove;

    bool wKingside {true};
    bool wQueenside {true};
    bool bKingside {true};
    bool bQueenside {true};
    // castle rights kingside and queenside
    
    std::vector<std::vector<Piece>> pieces;

public:
    Piece getPiece(int row, int column);
    std::string returnFEN();
    void setPosition(std::string FEN);
    Position(std::string FEN);
    Position();
    Position(Position* prev, std::string move);
};

#endif