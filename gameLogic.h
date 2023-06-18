#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
// if i #include "interface.h" everything falls apart


struct piecePos
{
    int rank;
    int file;
};

class Position
{
public:
    char onMove {'W'};
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
    bool isMoveLegal(piecePos curr, piecePos next);
    bool isPinned(piecePos curr);
    bool isInCheck(piecePos curr);
    bool isInBoardBounds(piecePos curr);
    bool areObstaclesSideway(piecePos curr, piecePos next);
    bool areObstaclesDiagonally(piecePos curr, piecePos next);
public:
    bool movePiece(piecePos curr, piecePos next);
    void setPosition(std::string FEN);
    std::string returnFEN();
    Position(std::string FEN);
    Position();
    Position(Position* prev, std::string move);
};

#endif