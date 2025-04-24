#include "const.h"
#include "piecePos.h"

bool PiecePos::isInBoardBounds()
{
    if (rank > 7 || rank < 0)
    {
        return false;
    }
    else if (file > 7 || file < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// returns a bitboard with a single piece on it
bitboard PiecePos::returnBitboard()
{
    bitboard temp {1};
    temp <<= file + rank * 8;
    return temp;
}


bool operator== (const PiecePos i, const PiecePos j)
{
    return (i.rank == j.rank && i.file == j.file);
}
