#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <cstdint>
#include <SFML/Graphics.hpp>

typedef std::uint64_t bitboard;

enum class Pieces
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

class PiecePos
{
public:
    int rank; // 1, ... (1st rank is 0)
    int file; // A, ...

    bitboard returnBitboard();
    bool isInBoardBounds();
    friend bool operator== (const PiecePos i, const PiecePos j);
};

class Position
{
public:
    size_t moves {0};
    size_t halfmoves {0};

    bool whiteOnMove {true};
    std::string enpassant {"-"};
    std::string moveNotation;
    std::string FEN;

    std::unique_ptr<Position> prev;
    std::unique_ptr<Position> next;

    // castle rights kingside and queenside
    bool wKingside {true}; 
    bool wQueenside {true};
    bool bKingside {true};
    bool bQueenside {true};

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
    bitboard enpassantSquare {0};

private:
    bool isInCheck();
    bool areLegalMovesLeft();
    bool invalidPawnMove(PiecePos curr, PiecePos next);
    bool invalidRookMove(PiecePos curr, PiecePos next);
    bool invalidKnightMove(PiecePos curr, PiecePos next);
    bool invalidBishopMove(PiecePos curr, PiecePos next);
    bool invalidKingMove(PiecePos curr, PiecePos next);
    bool legalCastle(PiecePos curr, PiecePos next);
public:
    bool isMoveLegal(PiecePos curr, PiecePos next);
    bool movePiece(PiecePos curr, PiecePos next);
    
    // std::string moveToAlgebraicNotation(piecePos curr, piecePos next);
    std::string returnFEN();
    void setPosition(std::string FEN);

    // Position(std::string FEN);
    // Position();
    // Position(Position* const prev, piecePos curr, piecePos next);
};


size_t binaryHammingWeight(std::uint64_t in);
PiecePos bitboardToPiecePos(bitboard piece);

#endif