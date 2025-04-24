#include <iostream>
#include <tuple>
#include <array>
#include <chrono>
#include <thread>


#include "gameLogic.h"
#include "interface.h"


// returns threats to the piece
bitboard Position::isInCheck(PiecePos curr)
{
    // if the king can take the piece using the moves of that piece then that piece can take the king
    // eg. if king can take knight witk L shaped move then the knight checks the king
    
    // offsets index of pieces by a color (white +6 to so index shows black pieces)
    size_t colorIndex {0};
    if (whiteOnMove)
    {
        colorIndex = 6;
    }

    bitboard inCheck {false};

    // for all pieces
    for (size_t pieceIndex {0}; pieceIndex < 6; pieceIndex++)
    {
        switch (pieceIndex)
        {
            case 0:
                inCheck |= legalPawnTakes(curr) & pieces.at(pieceIndex + colorIndex);
                break;
            case 1:
                inCheck |= legalRookMoves(curr) & pieces.at(pieceIndex + colorIndex);
                break;
            case 2:
                inCheck |= legalKnightMoves(curr) & pieces.at(pieceIndex + colorIndex);
                break;
            case 3:
                inCheck |= legalBishopMoves(curr) & pieces.at(pieceIndex + colorIndex);
                break;
            case 4:
                inCheck |= legalQueenMoves(curr) & pieces.at(pieceIndex + colorIndex);
                break;
            case 5:
                inCheck |= legalKingMoves(curr) & pieces.at(pieceIndex + colorIndex);
                break;
        }
    }

    return inCheck;
}


bitboard Position::isInCheck()
{
    if (whiteOnMove)
    {
        return isInCheck(bitboardToPiecePos(pieces.at(static_cast<size_t>(Pieces::wKing))));       
    }
    else
    {
        return isInCheck(bitboardToPiecePos(pieces.at(static_cast<size_t>(Pieces::bKing))));       
    }
}


bool Position::areLegalMovesLeft()
{
    for (int i {0}; i < 64; i++)
    {
        if (legalMoves({i % 8, i / 8}))
        {
            return true;
        }
    }
    return false;
}


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
    bitboard oppositePieces {0};
    bitboard c {curr.returnBitboard()};
    bitboard firstMove {0};

    // by multiplying im shifting bit by 7 (128), 8 (256), 9 (512)...
    if (whiteOnMove)
    {
        legalMoves = c * 256;

        firstMove = SECONDRANK;

        oppositePieces = allBlackPieces();

        if (static_cast<bool>(firstMove & c))
        {
            if (!(static_cast<bool>(oppositePieces & c * 256)))
            {
                legalMoves += c * 65536;
            }
        }
    }
    else
    {
        legalMoves = c / 256;

        firstMove = SEVENTHRANK;

        oppositePieces = allWhitePieces();
        
        if (static_cast<bool>(firstMove & c))
        {
            if (!(static_cast<bool>(oppositePieces & c / 256)))
            {
                legalMoves += c / 65536;
            }
        }
    }

    // pieces you cannot take
    legalMoves = minusYourPieces(legalMoves);
    // and pieces ahead of you
    legalMoves -= legalMoves & oppositePieces;

    // pieces you can take
    legalMoves += legalPawnTakes(curr);

    return legalMoves;
}


bitboard Position::legalPawnTakes(PiecePos curr)
{
    bitboard c {curr.returnBitboard()};
    bitboard legalTakes {0};
    bool onAFile {static_cast<bool>(AFILE & c)};
    bool onHFile {static_cast<bool>(HFILE & c)};
    bitboard oppositePieces {0};

    // by multiplying im shifting bit by 7 (128), 8 (256), 9 (512)...
    if (whiteOnMove)
    {
        
        if (!onAFile)
        {
            legalTakes += c * 128;
        }

        if (!onHFile)
        {
            legalTakes += c * 512;
        }

        oppositePieces = allBlackPieces();
    }
    else
    {
        if (!onAFile)
        {
            legalTakes += c / 512;
        }

        if (!onHFile)
        {
            legalTakes += c / 128;
        }

        oppositePieces = allWhitePieces();
    }
    
    oppositePieces |= enpassantSquare;
    return legalTakes & oppositePieces;
}


bitboard Position::legalRookMoves(PiecePos curr)
{
    bitboard c = curr.returnBitboard();
    bitboard tempRank {AFILE};
    bitboard tempFile {FIRSTRANK};
    for (; !(tempRank & c); tempRank *= 2)
    {
        ;
    }

    
    for (; !(tempFile & c); tempFile <<= 8)
    {
        ;
    }

    // check for colisions
    bitboard opponentPieces;
    bitboard currentPieces;
    if (whiteOnMove)
    {
        currentPieces = allWhitePieces() - c;
        opponentPieces = allBlackPieces();
    }
    else
    {
        currentPieces = allBlackPieces() - c;
        opponentPieces = allWhitePieces();
    }

    bitboard verticalMoves {0};
    // north
    for (bitboard i {c << 8}; i != 0; i <<= 8)
    {
        if (i & currentPieces)
        {
            break;
        }

        verticalMoves += i;
        if (i & opponentPieces)
        {
            break;
        }
    }

    // south
    for (bitboard i {c >> 8}; i != 0; i >>= 8)
    {
        if (i & currentPieces)
        {
            break;
        }

        verticalMoves += i;
        if (i & opponentPieces)
        {
            break;
        }
    }

    // east
    // ends if i is on A file
    bitboard notAFile {~AFILE};
    for (bitboard i {c << 1}; i & notAFile; i <<= 1)
    {
        if (i & currentPieces)
        {
            break;
        }

        verticalMoves += i;
        if (i & opponentPieces)
        {
            break;
        }
    }

    // // west
    bitboard notHFile {~HFILE};
    for (bitboard i {c >> 1}; i & notHFile; i >>= 1)
    {
        if (i & currentPieces)
        {
            break;
        }

        verticalMoves += i;
        if (i & opponentPieces)
        {
            break;
        }
    }

    bitboard legalMoves {verticalMoves};
    return legalMoves;
}


bitboard Position::legalKnightMoves(PiecePos curr)
{
    bitboard c {curr.returnBitboard()};
    bitboard legalMoves {0};

    // prevent wraping moves around side edges of the board (eg.: H1 <<= 1 is A2)
    bool onAFile {static_cast<bool>(AFILE & c)};
    bool onBFile {static_cast<bool>(BFILE & c)};
    bool onGFile {static_cast<bool>(GFILE & c)};
    bool onHFile {static_cast<bool>(HFILE & c)};

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
    bitboard c = curr.returnBitboard();
    bitboard opponentPieces;
    bitboard currentPieces;
    if (whiteOnMove)
    {
        currentPieces = allWhitePieces() - c;
        opponentPieces = allBlackPieces();
    }
    else
    {
        currentPieces = allBlackPieces() - c;
        opponentPieces = allWhitePieces();
    }

    bitboard legalMoves {0};
    // north east
    bitboard cCopy = c << 9;
    for (PiecePos i {curr}; i.rank != 7 && i.file != 7; i.rank++, i.file++, cCopy <<= 9)
    {
        if (cCopy & currentPieces)
        {
            break;
        }

        legalMoves += cCopy;
        if (cCopy & opponentPieces)
        {
            break;
        }
    }

    // north west
    cCopy = c << 7;
    for (PiecePos i {curr}; i.rank != 7 && i.file != 0; i.rank++, i.file--, cCopy <<= 7)
    {
        if (cCopy & currentPieces)
        {
            break;
        }

        legalMoves += cCopy;
        if (cCopy & opponentPieces)
        {
            break;
        }
    }

    // south west
    cCopy = c >> 9;
    for (PiecePos i {curr}; i.rank != 0 && i.file != 0; i.rank--, i.file--, cCopy >>= 9)
    {
        if (cCopy & currentPieces)
        {
            break;
        }

        legalMoves += cCopy;
        if (cCopy & opponentPieces)
        {
            break;
        }
    }

    // south east
    cCopy = c >> 7;
    for (PiecePos i {curr}; i.rank != 0 && i.file != 7; i.rank--, i.file++, cCopy >>= 7)
    {
        if (cCopy & currentPieces)
        {
            break;
        }

        legalMoves += cCopy;
        if (cCopy & opponentPieces)
        {
            break;
        }
    }

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
    bool onAFile {static_cast<bool>(AFILE & c)};
    bool onHFile {static_cast<bool>(HFILE & c)};
    bitboard legalMoves {0};
    
    if (onAFile)
    {                           // 00000011
        legalMoves = 0x60406;   // 00000001
    }                           // 00000011
    else if (onHFile)
    {                           // 00000110
        legalMoves = 0x30103;   // 00000100
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

    legalMoves = minusYourPieces(legalMoves);
    return legalMoves;
}


bitboard Position::legalCastle(PiecePos curr)
{
    bitboard c {curr.returnBitboard()};
    // check the castling rights and if the king is selected
    if (whiteOnMove)
    {
        if (!(wQueenside || wKingside))
        {
            return 0;
        }

        if (!(static_cast<bool>(c & pieces.at(static_cast<size_t>(Pieces::wKing)))))
        {
            return 0;
        }
    }
    else
    {
        if (!(bQueenside || bKingside))
        {
            return 0;
        }

        if (!(static_cast<bool>(c & pieces.at(static_cast<size_t>(Pieces::bKing)))))
        {
            return 0;
        }
    }
    
    if (isInCheck(curr))
    {
        return 0;
    }
    
    bitboard blockingPieces {allWhitePieces() + allBlackPieces()};
    bitboard legalMoves {0};
    if (whiteOnMove)
    {
        if (wKingside)
        {
            if (isInCheck({curr.rank, curr.file + 1}) || isInCheck({curr.rank, curr.file + 1}))
            {
                return 0;
            }

            if (!static_cast<bool>(blockingPieces & WCASTLEKINGSIDE))
            {
                legalMoves += 0x80;
            }
        }
        
        if (wQueenside)
        {
            if (isInCheck({curr.rank, curr.file - 1}) || isInCheck({curr.rank, curr.file - 1}))
            {
                return 0;
            }

            if (!static_cast<bool>(blockingPieces & WCASTLEQUEENSIDE))
            {
                legalMoves += 0x01;
            }
        }
    }
    else
    {
        if (bQueenside)
        {
            if (isInCheck({curr.rank, curr.file - 1}) || isInCheck({curr.rank, curr.file - 2}))
            {
                return 0;
            }

            if (!static_cast<bool>(blockingPieces & BCASTLEQUEENSIDE))
            {
                legalMoves += BQUEENSIDEROOK;
            }
        }

        if (bKingside)
        {
            if (isInCheck({curr.rank, curr.file + 1}) || isInCheck({curr.rank, curr.file + 2}))
            {
                return 0;
            }

            if (!static_cast<bool>(blockingPieces & BCASTLEKINGSIDE))
            {
                legalMoves += BKINGSIDEROOK;
            }
        }
    }

    return legalMoves;
}


void Position::handleCastlingRights(PiecePos curr, size_t movedIndex)
{
    switch (static_cast<Pieces>(movedIndex))
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
}


std::tuple<bitboard, bitboard> Position::makeMove(bitboard movedPiece, bitboard takenPiece, size_t movedIndex, size_t takenIndex)
{
    bitboard pastMoved {pieces.at(movedIndex)};
    bitboard pastTaken {0};

    // if there was piece to take
    if (takenIndex != 12)
    {
        pastTaken = pieces.at(takenIndex);
        // then take it
        pieces.at(takenIndex) -= takenPiece;
    }

    // move picked piece to a new position
    pieces.at(movedIndex) -= movedPiece;
    pieces.at(movedIndex) += takenPiece;
        
    // take while enpassant
    // only if pawn takes
    if (movedIndex % 6 == 0)
    {
        if (enpassantSquare & takenPiece)
        {
            if (whiteOnMove)
            {
                pastTaken = pieces.at(static_cast<size_t>(Pieces::bPawn));
                bitboard enpassant {takenPiece >> 8};
                pieces.at(static_cast<size_t>(Pieces::bPawn)) -= enpassant;
            }
            else
            {
                pastTaken = pieces.at(static_cast<size_t>(Pieces::wPawn));
                bitboard enpassant {takenPiece << 8};
                pieces.at(static_cast<size_t>(Pieces::wPawn)) -= enpassant;
            }
        } 
    }

    // castle
    // rook is already taken so I dont have to subtract it
    if (whiteOnMove)
    {
        if (movedPiece & WKING && takenPiece & WQUEENSIDEROOK)
        {
            pieces.at(static_cast<size_t>(Pieces::wKing)) = WQUEENSIDEKINGMOVE;
            pieces.at(static_cast<size_t>(Pieces::wRook)) += WQUEENSIDEROOKMOVE;
        }
        else if (movedPiece & WKING && takenPiece & WKINGSIDEROOK)
        {
            pieces.at(static_cast<size_t>(Pieces::wKing)) = WKINGSIDEKINGMOVE;
            pieces.at(static_cast<size_t>(Pieces::wRook)) += WKINGSIDEROOKMOVE;
        }
    }
    else
    {
        if (movedPiece & BKING && takenPiece & BQUEENSIDEROOK)
        {
            pieces.at(static_cast<size_t>(Pieces::bKing)) = BQUEENSIDEKINGMOVE;
            pieces.at(static_cast<size_t>(Pieces::bRook)) += BQUEENSIDEROOKMOVE;
        }
        else if (movedPiece & BKING && takenPiece & BKINGSIDEROOK)
        {
            pieces.at(static_cast<size_t>(Pieces::bKing)) = BKINGSIDEKINGMOVE;
            pieces.at(static_cast<size_t>(Pieces::bRook)) += BKINGSIDEROOKMOVE;
        }
    }

    return {pastMoved, pastTaken};
}


void Position::unmakeMove(std::tuple<bitboard, bitboard> past, size_t movedIndex, size_t takenIndex)
{
    pieces.at(movedIndex) = std::get<0>(past);
    if (takenIndex != 12)
    {
        pieces.at(takenIndex) = std::get<1>(past);
    }
}

// returns true if white
bool Position::indexToSide(size_t index)
{
    if (index < 6)
    {
        return true;
    }
    else if (index < 12)
    {
        return false;
    }
    else
    {
        std::cerr << "Index over 11: " << index << '\n';
        return whiteOnMove;
    }
}


bitboard Position::pseudoLegalMoves(PiecePos curr)
{
    // check if any given rank/file is within the chessboard bounds
    if (!curr.isInBoardBounds())
    {
        return 0;
    }

    // find a kind of a piece that was chosen (index in pieces[])
    bitboard currPiece = curr.returnBitboard();
    size_t indexCurr {findPiece(curr.returnBitboard())};
    
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
            return legalKingMoves(curr) + legalCastle(curr);
        default:
        {
            std::cerr << "isMoveLegal(): should never happen - switch default\n";
            return 0;
        }
    }

    std::cerr << "isMoveLegal(): should never happen - end\n";
    return 0;
}

// return actually legal moves, resource intensive (?)
bitboard Position::legalMoves(PiecePos curr)
{
    Position temp = *this;
    size_t indexTaken {12};
    size_t indexMoved {findPiece(curr.returnBitboard())};
    bitboard movedPiece {curr.returnBitboard()};
    
    bitboard draftOfLegalMoves = pseudoLegalMoves(curr);
    bitboard square {1};

    for (size_t i {0}; i < 64; i++, square <<= 1)
    {
        // reset to invalid value
        indexTaken = 12;
        if (draftOfLegalMoves & square)
        {
            indexTaken = temp.findPiece(square);
            std::tuple<bitboard, bitboard> past = temp.makeMove(movedPiece, square, indexMoved, indexTaken);
            if (temp.isInCheck())
            {
                draftOfLegalMoves -= square;
            }

            temp.unmakeMove(past, indexMoved, indexTaken);
        }
    }

    return draftOfLegalMoves;
}


// calls isMoveLegal(), moves a piece, changes the castle rights and ensures the same side cannot move twice
bool Position::movePiece(PiecePos curr, PiecePos next)
{
    bitboard currPiece = curr.returnBitboard();
    bitboard nextPiece = next.returnBitboard();
    bitboard legalMoves = this->pseudoLegalMoves(curr);
    
    // no legal moves
    if (!legalMoves)
    {
        return false;
    }

    // illegal move
    if (!(legalMoves & nextPiece))
    {
        return false;
    }

    // find a kind of a piece on a destination square
    size_t indexCurr {findPiece(currPiece)};

    // find a kind of a piece on a destination square
    size_t indexNext {findPiece(nextPiece)};

    // move piece (including enpassant)
    std::tuple<bitboard, bitboard> past = makeMove(currPiece, nextPiece, indexCurr, indexNext);

    // if inCheck() then unmakeMove and return false
    if (isInCheck())
    {
        unmakeMove(past, indexCurr, indexNext);
        return false;
    }

    // TODO: promote pawns

    // handle rights and rules after making a move
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

    // castling rights
    handleCastlingRights(curr, indexCurr);

    // now the opposite side moves
    if (whiteOnMove)
    {
        whiteOnMove = false;
    }
    else
    {
        whiteOnMove = true;
    }
    
    // if not changed the enpassantsquare then reset enpassantSquare;
    if (!enpassantChanged)
    {
        enpassantSquare = 0;
        enpassantChanged = true;
    }
    
    if (!areLegalMovesLeft())
    {
        end = true;
    }

    return true;
}

// returns an index of array where the piece is, if not found returns 12
size_t Position::findPiece(bitboard piece)
{
    if (binaryHammingWeight(piece) != 1)
    {
        std::cerr << "findPiece() has bHW over 1\n";
        return INT_MAX;
    }

    size_t index {0};
    for (;index < 12; index++)
    {
        if (pieces.at(index) & piece)
        {
            return index;
        }
    }

    return index;
}


size_t binaryHammingWeight(bitboard in) // by Peter Wegner (1960)
{
    size_t count = 0;
    while (in) {
        count++;
        in &= in - 1; // reset LS1B
    }
    return count;
}

// bitboard to PiecePos, returns {-1, -1} if error
PiecePos bitboardToPiecePos(bitboard piece)
{
    if (binaryHammingWeight(piece) != 1)
    {
        return {-1, -1};
    }

    int j {0};
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
