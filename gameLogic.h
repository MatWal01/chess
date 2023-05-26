#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "interface.h"


class Position
{
public:
    char onMove;
    std::string move;

    std::unique_ptr<Position> prev;
    std::unique_ptr<Position> next;

    // castle rights kingside and queenside
    bool wKingside {true};
    bool wQueenside {true};
    bool bKingside {true};
    bool bQueenside {true};
    
    std::vector<std::vector<char>> pieces;

private:
    bool isMoveLegal(int pieceRank, int pieceFile, int newRank, int newFile);
    bool isPinned(int pieceRank, int pieceFile);
    bool isInCheck(int pieceRank, int pieceFile);
public:
    bool movePiece(int pieceFile, int pieceRank, int newFile, int newRank);
    void drawPosition(sf::RenderWindow* window, GameGraphics* ui);
    void setPosition(std::string FEN);
    std::string returnFEN();
    Position(std::string FEN);
    Position();
    Position(Position* prev, std::string move);
};

#endif