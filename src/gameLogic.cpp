#include <iostream>
#include <bitset>

#include "gameLogic.h"
#include "interface.h"


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
    temp <<= (file) + (rank) * 8;
    return temp;
}


bool operator== (const PiecePos i, const PiecePos j)
{
    return (i.rank == j.rank && i.file == j.file);
}

// TODO
bool Position::isInCheck()
{
    // no king on the board
    if (
        !(pieces.at(static_cast<int>(Pieces::wKing)))
        ||
        !(pieces.at(static_cast<int>(Pieces::bKing)))
        )
    {
        return false;
    }

    // TODO:
    // create a new position as if you had not made a move
    // if your king can be taken you are in check 

    return false;
}


// bool Position::areLegalMovesLeft()
// {
//     for (int i {0}; i < 8; i++)
//     {
//         for (int j {0}; j < 8; j++)
//         {
//             if (islower(pieces.at(i).at(j)) == islower(onMove))
//             {
//                 for (int rank {0}; rank < 8; rank++)
//                 {
//                     for (int file {0}; file < 8; file++)
//                     {
//                         if (isProperPieceMove({i, j}, {rank, file}))
//                         {
//                             if (isMoveLegal({i, j}, {rank, file}))
//                             {
//                                 return true;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     return false;
// }

// sum of white bitboards
bitboard Position::allWhitePieces()
{
    bitboard white {0};
    for (size_t i {0}; i <= static_cast<size_t>(Pieces::wKing); i++)
    {
        white += pieces.at(i);
    }

    return white;
}

// sum of black bitboards
bitboard Position::allBlackPieces()
{
    bitboard black {0};
    for (size_t i {static_cast<size_t>(Pieces::bPawn)}; i <= static_cast<size_t>(Pieces::bKing); i++)
    {
        black += pieces.at(i);
    }
    
    return black;
}

// used in legal<Piece>Moves()
bitboard Position::minusYourPieces(bitboard moves)
{
    // cannot take your piece
    if (whiteOnMove)
    {
        moves -= moves & allWhitePieces();
    }
    else
    {
        moves -= moves & allBlackPieces();
    }
    
    return moves;
}


bitboard Position::legalPawnMoves(PiecePos curr)
{
    bitboard legalMoves {0};
    bitboard legalTakes {0};
    bitboard oppositePieces {0};
    bitboard c {curr.returnBitboard()};
    bitboard firstMove {0};
    
    if (whiteOnMove)
    {
        legalMoves = c * 256;
        legalTakes = c * 512 + c * 128;

        firstMove = 0x000000000000FF00;

        oppositePieces = allBlackPieces();

        if (static_cast<bool>(firstMove & c))
        {
            legalMoves += c * 65536;
        }
    }
    else
    {
        legalMoves = c / 256;
        legalTakes = c / 512 + c / 128;
        
        firstMove = 0x00FF000000000000;

        oppositePieces = allWhitePieces();
        
        if (static_cast<bool>(firstMove & c))
        {
            legalMoves += c / 65536;
        }
    }


    // pieces you cannot take
    legalMoves = minusYourPieces(legalMoves);
    // and pieces ahead of you
    legalMoves -= legalMoves & oppositePieces;

    // pieces you can take
    oppositePieces |= enpassantSquare;
    legalMoves += (legalTakes & oppositePieces);

    return legalMoves;
}


bitboard Position::legalRookMoves(PiecePos curr)
{
    bitboard tempRank {0x101010101010101};
    bitboard tempFile {0xFF};
    bitboard c = curr.returnBitboard();
    for (; !(tempRank & c); tempRank *= 2)
    {
        ;
    }

    bitboard legalMoves {tempRank};
    
    for (; !(tempFile & c); tempFile <<= 8)
    {
        ;
    }

    legalMoves |= tempFile;
    legalMoves = minusYourPieces(legalMoves);
    return legalMoves;
}


bitboard Position::legalKnightMoves(PiecePos curr)
{
    bitboard c {curr.returnBitboard()};
    bitboard legalMoves {0};

    // prevent wraping moves around side edges of the board (eg.: H1 <<= 1 is A2)
    bool onAFile {static_cast<bool>(0x0101010101010101 & c)};
    bool onBFile {static_cast<bool>(0x0202020202020202 & c)};
    bool onGFile {static_cast<bool>(0x4040404040404040 & c)};
    bool onHFile {static_cast<bool>(0x8080808080808080 & c)};

    // 8 legal moves
    if (!onGFile && !onHFile)
    {
        legalMoves += c * 1024;
        legalMoves += c / 64;
    }

    if (!onHFile)
    {
        legalMoves += c * 131072;
        legalMoves += c / 32768;
    } 
    
    if (!onAFile)
    {
        legalMoves += c * 32768;
        legalMoves += c / 131072;
    }

    if (!onBFile && !onAFile)
    {
        legalMoves += c * 64;
        legalMoves += c / 1024;
    }

    legalMoves = minusYourPieces(legalMoves);
    return legalMoves;
}


bitboard Position::legalBishopMoves(PiecePos curr)
{
    // File - rank
    int fR {curr.file - curr.rank};
    // 7 - File - Rank
    int sFR {7 - curr.file - curr.rank};
    // diagonals
    // from A1 to H8
    bitboard diagA1H8 {0x8040201008040201};
    // from H1 to A8
    bitboard diagH1A8 {0x0102040810204080};

    // move up or down diagonals depending on position curr (point of intersection)
    if (fR > 0)
    {
        diagA1H8 >>= fR * 8;
    }
    else if (fR < 0)
    {
        fR *= -1;
        diagA1H8 <<= fR * 8;
    }
    
    if (sFR > 0)
    {
        diagH1A8 >>= sFR * 8;
    }
    else if (sFR < 0)
    {
        sFR *= -1;
        diagH1A8 <<= sFR * 8;
    }

    bitboard legalMoves {diagA1H8 | diagH1A8};

    legalMoves = minusYourPieces(legalMoves);
    return legalMoves;
}


bitboard Position::legalQueenMoves(PiecePos curr)
{
    bitboard legalMoves = legalRookMoves(curr) | legalBishopMoves(curr);
    return legalMoves;
}


bitboard Position::legalKingMoves(PiecePos curr)
{
    bitboard c = curr.returnBitboard();
    bool onAFile {static_cast<bool>(0x0101010101010101 & c)};
    bool onHFile {static_cast<bool>(0x8080808080808080 & c)};
    bitboard legalMoves {0};
    
    if (onAFile)
    {                           // 00000011
        legalMoves = 0x30103;   // 00000001
    }                           // 00000011
    else if (onHFile)
    {                           // 00000110
        legalMoves = 0x60406;   // 00000100
    }                           // 00000110
    else
    {                           // 00000111
        legalMoves = 0x70507;   // 00000101
    }                           // 00000111

    // align moves to where the king is
    int shift {0};
    for (; c != 0; c >>= 1)
    {
        shift++;
    }

    // center of the legalMoves is not at A1, therefore we have to subtract to align
    shift -= 10;
    if (shift < 0)
    {
        shift *= -1;
        legalMoves >>= shift;
    }
    else
    {
        legalMoves <<= shift;
    }

    // prevent taking pieces of the same color
    bitboard sameColor {0};
    if (whiteOnMove)
    {
        sameColor = allWhitePieces();
    }
    else
    {
        sameColor = allBlackPieces();
    }
    legalMoves -= (legalMoves & sameColor);

    // TODO: add castling in the future

    legalMoves = minusYourPieces(legalMoves);
    return legalMoves;
}


bitboard Position::legalCastle()
{
    if (whiteOnMove)
    {
        if (!(wQueenside || wKingside))
        {
            return false;
        }
    }
    else
    {
        if (!(bQueenside || bKingside))
        {
            return false;
        }
    }
    
    if (isInCheck())
    {
        return false;
    }
    
    // if (invalidRookMove(curr, next))
    // {
    //     return false;
    // }
    // if (king == 'K')
    // {
    //     if (curr.rank == 0 && next.rank == 0)
    //     {
    //         if (curr.file == next.file + 2 && wQueenside)
    //         {
    //             return true;
    //         }
    //         else if (curr.file == next.file - 2 && wKingside)
    //         {
    //             return true;
    //         }
    //     }
    // }
    // else if (king == 'k')
    // {
    //     if (curr.rank == 7 && next.rank == 7)
    //     {
    //         if (curr.file == next.file + 2 && bQueenside)
    //         {
    //             return true;
    //         }
    //         else if (curr.file == next.file - 2 && bKingside)
    //         {
    //             return true;
    //         }
    //     }
    // }

    return false;
}


bitboard Position::legalMoves(PiecePos curr)
{
    // check if any given rank/file is within the chessboard bounds
    if (!curr.isInBoardBounds())
    {
        return 0;
    }

    // find a kind of a piece that was chosen (index in pieces[])
    bitboard currPiece = curr.returnBitboard();
    size_t indexCurr {0};
    for (; indexCurr < pieces.size(); indexCurr++)
    {
        if (currPiece & pieces.at(indexCurr))
        {
            break;
        }
    }
    
    // no pieces at selected square
    if (indexCurr == 12)
    {
        return 0;
    }

    // check if correct piece colour was chosen
    if (whiteOnMove)
    {
        if (indexCurr > static_cast<size_t>(Pieces::wKing))
        {
            return 0;
        }
    }
    else
    {
        if (indexCurr <= static_cast<size_t>(Pieces::wKing))
        {
            return 0;
        }
    }

    switch (indexCurr % 6)
    {
        case 0:
            return legalPawnMoves(curr);
        case 1:
            return legalRookMoves(curr);
        case 2:
            return legalKnightMoves(curr);
        case 3:
            return legalBishopMoves(curr);
        case 4:
            return legalQueenMoves(curr);
        case 5:
            return legalKingMoves(curr);
        default:
        {
            std::cerr << "isMoveLegal(): should never happen - switch default\n";
            return 0;
        }
    }

    std::cerr << "isMoveLegal(): should never happen - end\n";
    return 0;
}

// calls isMoveLegal(), moves a piece, changes the castle rights and ensures the same side cannot move twice
bool Position::movePiece(PiecePos curr, PiecePos next)
{
    bitboard currPiece = curr.returnBitboard();
    bitboard nextPiece = next.returnBitboard();
    bitboard legalMoves = this->legalMoves(curr);
    
    if (!legalMoves)
    {
        return false;
    }

    if (!(legalMoves & nextPiece))
    {
        return false;
    }

    size_t indexCurr {0};
    // find a kind of a piece on a destination square
    for (; indexCurr < pieces.size(); indexCurr++)
    {
        if (currPiece & pieces.at(indexCurr))
        {
            break;
        }
    }

    size_t indexNext {0};
    // find a kind of a piece on a destination square
    for (; indexNext < pieces.size(); indexNext++)
    {
        if (nextPiece & pieces.at(indexNext))
        {
            // and take the piece
            pieces.at(indexNext) -= nextPiece;
            break;
        }
    }

    // remove picked piece from origin
    pieces.at(indexCurr) -= currPiece;

    // add selected piece
    pieces.at(indexCurr) += nextPiece;
    
    // if firstMove then add enpassantSquare
    bool enpassantChanged {false};
    if (indexCurr == static_cast<size_t>(Pieces::wPawn))
    {
        if (next.rank - curr.rank == 2)
        {
            PiecePos enpassantPos {curr.rank + 1, curr.file};
            enpassantSquare = enpassantPos.returnBitboard();
            enpassantChanged = true;
        }
    }
    else if (indexCurr == static_cast<size_t>(Pieces::bPawn))
    {
        if (next.rank - curr.rank == -2)
        {
            PiecePos enpassantPos {curr.rank - 1, curr.file};
            enpassantSquare = enpassantPos.returnBitboard();
            enpassantChanged = true;
        }
    }
    
    // take while enpassant
    if (static_cast<bool>(enpassantSquare & nextPiece))
    {
        if (whiteOnMove)
        {
            PiecePos enpassantPos {next.rank - 1, next.file};
            pieces.at(static_cast<size_t>(Pieces::bPawn)) -= enpassantPos.returnBitboard();
        }
        else
        {
            PiecePos enpassantPos {next.rank + 1, next.file};
            pieces.at(static_cast<size_t>(Pieces::wPawn)) -= enpassantPos.returnBitboard();
        }
    } 

    // else reset enpassantSquare;
    if (!enpassantChanged)
    {
        enpassantSquare = 0;
        enpassantChanged = true;
    }
    
    // castling rights
    switch (static_cast<Pieces>(indexCurr))
    {
        case Pieces::wRook:
        {
            if (curr.rank == 0)
            {
                if (curr.file == 0)
                {
                    wQueenside = false;
                }
                else if (curr.file == 7)
                {
                    wKingside = false;
                }
            }
            break;
        }
        case Pieces::wKing:
        {
            wQueenside = false;
            wKingside = false;
            break;
        }
        case Pieces::bRook:
        {
            if (curr.rank == 7)
            {
                if (curr.file == 0)
                {
                    wQueenside = false;
                }
                else if (curr.file == 7)
                {
                    wKingside = false;
                }
            }
            break;
        }
        case Pieces::bKing:
        {
            bQueenside = false;
            bKingside = false;
            break;
        }
    }

    // now the opposite side moves
    if (whiteOnMove)
    {
        whiteOnMove = false;
    }
    else
    {
        whiteOnMove = true;
    }

    return true;
}


// Position::Position(std::string FEN)
// {
//     setPosition(FEN);
// }


size_t binaryHammingWeight(bitboard in) // by Peter Wegner (1960)
{
    size_t count = 0;
    while (in) {
        count++;
        in &= in - 1; // reset LS1B
    }
    return count;
}


PiecePos bitboardToPiecePos(bitboard piece)
{
    if (binaryHammingWeight(piece) != 1)
    {
        return {-1, -1};
    }

    int j {1};
    for (bitboard i {1}; !(piece & i); i <<= 1)
    {
        j++;
    }

    return {(j / 8), (j % 8)};
}


// check if the piece you want to move is pinned to their king
// redundant use isInCheck(next) instead; also unfinished
// kept just because stackoverflow sugested to use goto there (and in 2 other places on the same day)
// bool Position::isPinned(piecePos curr)
// {
//     // find their king
//     char temp = pieces.at(curr.rank).at(curr.file);

//     if (temp == 'k' || temp == 'K')
//     {
//         return false;
//     }

//     int kingRank {-1};
//     int kingFile {-1};

//     for (size_t rank {0}; rank < 8; rank++)
//     {
//         for (size_t file {0}; file < 8; file++)
//         {       
//             if (
//                 toupper(pieces.at(rank).at(file)) == 'K'
//                 &&
//                 isupper(pieces.at(rank).at(file)) == islower(temp)
//                 )
//                 {
//                     kingRank = rank;
//                     kingFile = file;
//                     // use goto from there lmao??
//                 }
//         }
//     }

//     // check if piece is on the same file/rank as their king
//     if (curr.rank - kingRank == 0)
//     {
        
//     }
//     else if (curr.file - kingFile == 0)
//     {

//     }

//     // check if piece is on the same diagonal as their king
//     bool sameDiagonal {false};
    

//     return false;
// }
