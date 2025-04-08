#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <cstdint>
#include <SFML/Graphics.hpp>

// boolean representation of a chessboard (1 - piece is present, 0 - is not)
// 2^0 is A1 square 2^63 is H8 square
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
    bitboard allWhitePieces();
    bitboard allBlackPieces();
    bitboard minusYourPieces(bitboard moves);
    bitboard legalPawnMoves(PiecePos curr);
    bitboard legalRookMoves(PiecePos curr);
    bitboard legalKnightMoves(PiecePos curr);
    bitboard legalBishopMoves(PiecePos curr);
    bitboard legalQueenMoves(PiecePos curr);
    bitboard legalKingMoves(PiecePos curr);
    bitboard legalCastle();
public:
    bitboard legalMoves(PiecePos curr);
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