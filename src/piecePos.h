#pragma once
#include "const.h"

class PiecePos
{
public:
    int rank; // 1, ... (1st rank is 0)
    int file; // A, ...

    bitboard returnBitboard();
    bool isInBoardBounds();
    friend bool operator== (const PiecePos i, const PiecePos j);
};
