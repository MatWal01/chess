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

    size_t moves {0};
    size_t halfmoves {0};

    char onMove {'W'};
    std::string move;
    std::string FEN;

    std::unique_ptr<Position> prev;
    std::unique_ptr<Position> next;

    // castle rights kingside and queenside
    bool wKingside {true};
    bool wQueenside {true};
    bool bKingside {true};
    bool bQueenside {true};
    
    std::vector<std::vector<char>> pieces;

private:
    bool isInCheck();
    bool isInCheck(piecePos curr, piecePos next);
    bool isInBoardBounds(piecePos curr);
    bool invalidRookMove(piecePos curr, piecePos next);
    bool invalidDiagonalMove(piecePos curr, piecePos next);
public:
    bool isMoveLegal(piecePos curr, piecePos next);
    bool movePiece(piecePos curr, piecePos next);
    void setPosition(std::string FEN);
    std::string returnFEN();
    Position(std::string FEN);
    Position();
    Position(Position* const prev, piecePos curr, piecePos next);
};

#endif