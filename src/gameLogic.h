#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <cstdint>
#include <SFML/Graphics.hpp>

typedef std::uint64_t bitboard;

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
    
    std::array<bitboard, 12> pieces
    {
        0x000000000000FF00, // white pawn
        0x0000000000000081, // R
        0x0000000000000042, // N
        0x0000000000000024, // B
        0x0000000000000008, // Q
        0x0000000000000010, // K
        0x00FF000000000000, // black pawn
        0x8100000000000000, // ...
        0x4200000000000000,
        0x2400000000000000,
        0x0800000000000000,
        0x1000000000000000
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
    
    // std::string moveToAlgebraicNotation(piecePos curr, piecePos next);
    std::string returnFEN();
    void setPosition(std::string FEN);

    // Position(std::string FEN);
    // Position();
    // Position(Position* const prev, piecePos curr, piecePos next);
};

#endif