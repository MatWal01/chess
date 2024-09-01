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
    std::string enpassant {"-"};
    std::string moveNotation;
    std::string FEN;

    std::unique_ptr<Position> prev;
    std::unique_ptr<Position> next;

    // castle rights kingside and queenside
    bool wKingside {false}; 
    bool wQueenside {false};
    bool bKingside {false};
    bool bQueenside {false};

    bool end {false};
    
    std::vector<std::vector<char>> pieces {
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'}
        };

private:
    bool isInCheck();
    bool areLegalMovesLeft();
    bool isInBoardBounds(piecePos curr);
    bool legalEnpassant(piecePos curr, piecePos next);
    bool invalidRookMove(piecePos curr, piecePos next);
    bool invalidDiagonalMove(piecePos curr, piecePos next);
    bool legalCastle(piecePos curr, piecePos next);
public:
    bool isMoveLegal(piecePos curr, piecePos next);
    bool isInCheck(piecePos curr, piecePos next);
    bool isProperPieceMove(piecePos curr, piecePos next);
    bool movePiece(piecePos curr, piecePos next);
    
    std::string moveToAlgebraicNotation(piecePos curr, piecePos next);
    std::string returnFEN();
    void setPosition(std::string FEN);

    Position(std::string FEN);
    Position();
    Position(Position* const prev, piecePos curr, piecePos next);
};

#endif