#pragma once
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <cstdint>
#include <tuple>
#include <SFML/Graphics.hpp>

#include "const.h"
#include "piecePos.h"

// boolean representation of a chessboard (1 - piece is present, 0 - is not)
// 2^0 is A1 square 2^63 is H8 square
typedef std::uint64_t bitboard;
class Interface;

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

class Position
{
public:
    size_t moves {0};
    size_t halfmoves {0};

    bool whiteOnMove {true};

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
    bool areLegalMovesLeft();
    bitboard isInCheck(PiecePos curr);

    bitboard activity();
    bitboard threats();

    bitboard allWhitePieces();
    bitboard allBlackPieces();
    bitboard minusYourPieces(bitboard moves);

    bitboard legalPawnMoves(PiecePos curr);
    bitboard legalPawnTakes(PiecePos curr);
    bitboard legalRookMoves(PiecePos curr);
    bitboard legalKnightMoves(PiecePos curr);
    bitboard legalBishopMoves(PiecePos curr);
    bitboard legalQueenMoves(PiecePos curr);
    bitboard legalKingMoves(PiecePos curr);
    bitboard legalCastle(PiecePos curr);
    void handleCastlingRights(PiecePos curr, size_t movedIndex);
    
    std::tuple<bitboard, bitboard> makeMove(bitboard movedPiece, bitboard takenPiece, size_t movedIndex, size_t takenIndex);
    void unmakeMove(std::tuple<bitboard, bitboard> past, size_t movedIndex, size_t takenIndex);
public:
    bitboard isInCheck();
    // returns whiteOnMove
    bool indexToSide(size_t index);
    bitboard pseudoLegalMoves(PiecePos curr);
    // return actually legal moves, resource intensive (?)
    bitboard legalMoves(PiecePos curr);
    bool movePiece(PiecePos curr, PiecePos next);
    size_t findPiece(bitboard piece);

    // Position();
    // Position(const Position* prev, PiecePos curr, PiecePos next);
};

// returns an index of a piece in array
size_t binaryHammingWeight(bitboard in);
PiecePos bitboardToPiecePos(bitboard piece);
