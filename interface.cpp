#include <iostream>
#include "interface.h"
#include "gameLogic.h"


void GameGraphics::leftMouseInteract(sf::RenderWindow* const window, Position* const curr)
{
    mouseF = window->mapPixelToCoords(mouse);
    if (board.contains(mouseF))
    {
        if (firstClick == false)
        {
            firstClick = true;
            firstPos.file = mouse.x / 100.f;
            firstPos.rank = 7 - mouse.y / 100.f + 1;
            picked.setPosition(firstPos.file * pieceSize, (7 - firstPos.rank) * pieceSize);
            getLegalMoves(curr);
        }
        else if(secondClick == false)
        {
            secondPos.file = mouse.x / 100.f;
            secondPos.rank = 7 - mouse.y / 100.f + 1;
            secondClick = true;
            if (secondPos.file == firstPos.file && secondPos.rank == firstPos.rank)
            {
                firstClick = false;
                secondClick = false;
            }
        }
    }

    if (firstClick == true && secondClick == true)
    {
        firstClick = false;
        secondClick = false;

        if (!curr->movePiece(firstPos, secondPos))
        {
            firstPos.file = mouse.x / 100.f;
            firstPos.rank = 7 - mouse.y / 100.f + 1;
            picked.setPosition(firstPos.file * pieceSize, (7 - firstPos.rank) * pieceSize);
        }
        picked.setPosition({chessboardSize, chessboardSize});
        resetLegalMoves();
    }
}


void GameGraphics::resetPicked()
{
    firstClick = false;
    secondClick = false;
    picked.setPosition(chessboardSize, chessboardSize);
    resetLegalMoves();
}


void GameGraphics::drawChessboard(sf::RenderWindow* const window)
{
    window->draw(chessboard);
}


void GameGraphics::drawPosition(sf::RenderWindow* const window, Position* const pos)
{
    for (int i {7}; i >= 0; i--)
        {
            for (size_t j {0}; j < 8; j++)
            {
                char temp = pos->pieces.at(j).at(i);
                if (temp == '\0')
                {
                    continue;
                }
                sf::Sprite tempDraw = returnSprite(temp);
                tempDraw.move(pieceSize * i, pieceSize * (7 - j));
                window->draw(tempDraw);
            }
        }
}


void GameGraphics::getLegalMoves(Position* const pos)
{
    for (int rank {0}; rank < 8; rank++)
    {
        for (int file {0}; file < 8; file++)
        {
            legalMoves[rank][file] = pos->isMoveLegal(firstPos, {rank, file});
        }
    }
}


void GameGraphics::resetLegalMoves()
{
    for (int rank {0}; rank < 8; rank++)
    {
        for (int file {0}; file < 8; file++)
        {
            legalMoves[rank][file] = false;
        }
    }
}


void GameGraphics::drawLegalMoves(sf::RenderWindow* const window, Position* const pos)
{
    for (int rank {0}; rank < 8; rank++)
    {
        for (int file {0}; file < 8; file++)
        {
            if (legalMoves[rank][file])
            {
                legalMove.setPosition(file * pieceSize + circleOffset, (7 - rank) * pieceSize + circleOffset);
                window->draw(legalMove);
            }
        }
    }
}


sf::Sprite GameGraphics::returnSprite(char piece)
{
    switch (piece)
    {        
        // white pieces
        case 'P':
            return whitePawn;
        case 'R':
            return whiteRook;
        case 'N':
            return whiteKnight;
        case 'B':
            return whiteBishop;
        case 'Q':
            return whiteQueen;
        case 'K':
            return whiteKing;
        
        // black pieces
        case 'p':
            return blackPawn;
        case 'r':
            return blackRook;
        case 'n':
            return blackKnight;
        case 'b':
            return blackBishop;
        case 'q':
            return blackQueen;
        case 'k':
            return blackKing;
        
        // no piece
        case '\0':
            return whiteKing;
        default:
            return blackKing;

    }
}


sf::Sprite* GameGraphics::shareSprite(char temp)
{
    switch (temp)
    {        
        // white pieces
        case 'P':
            return &whitePawn;
        case 'R':
            return &whiteRook;
        case 'N':
            return &whiteKnight;
        case 'B':
            return &whiteBishop;
        case 'Q':
            return &whiteQueen;
        case 'K':
            return &whiteKing;
        
        // black pieces
        case 'p':
            return &blackPawn;
        case 'r':
            return &blackRook;
        case 'n':
            return &blackKnight;
        case 'b':
            return &blackBishop;
        case 'q':
            return &blackQueen;
        case 'k':
            return &blackKing;
        
        // no piece
        case '\0':
            return &whiteKing;
        default:
            return &blackKing;

    }
}


bool GameGraphics::loadGameTextures()
{
    if (!chessboardTexture.loadFromFile("textures/chessboard.png"))
    {
        return false;
    }
    // white pieces
    if (!whitePawnTexture.loadFromFile("textures/wPawn.png"))
    {
        return false;
    }
    if (!whiteRookTexture.loadFromFile("textures/wRook.png"))
    {
        return false;
    }
    if (!whiteKnightTexture.loadFromFile("textures/wKnight.png"))
    {
        return false;
    }
    if (!whiteBishopTexture.loadFromFile("textures/wBishop.png"))
    {
        return false;
    }
    if (!whiteQueenTexture.loadFromFile("textures/wQueen.png"))
    {
        return false;
    }
    if (!whiteKingTexture.loadFromFile("textures/wKing.png"))
    {
        return false;
    }

    // black pieces
    if (!blackPawnTexture.loadFromFile("textures/bPawn.png"))
    {
        return false;
    }
    if (!blackRookTexture.loadFromFile("textures/bRook.png"))
    {
        return false;
    }
    if (!blackKnightTexture.loadFromFile("textures/bKnight.png"))
    {
        return false;
    }
    if (!blackBishopTexture.loadFromFile("textures/bBishop.png"))
    {
        return false;
    }
    if (!blackQueenTexture.loadFromFile("textures/bQueen.png"))
    {
        return false;
    }
    if (!blackKingTexture.loadFromFile("textures/bKing.png"))
    {
        return false;
    }
    
    return true;
}


void GameGraphics::setTextures()
{

    whitePawnTexture.setSmooth(true);
    whiteRookTexture.setSmooth(true);
    whiteKnightTexture.setSmooth(true);
    whiteBishopTexture.setSmooth(true);
    whiteQueenTexture.setSmooth(true);
    whiteKingTexture.setSmooth(true);
    
    blackPawnTexture.setSmooth(true);
    blackRookTexture.setSmooth(true);
    blackKnightTexture.setSmooth(true);
    blackBishopTexture.setSmooth(true);
    blackQueenTexture.setSmooth(true);
    blackKingTexture.setSmooth(true);

    chessboard.setTexture(chessboardTexture);

    whitePawn.setTexture(whitePawnTexture);
    whiteRook.setTexture(whiteRookTexture);
    whiteKnight.setTexture(whiteKnightTexture);
    whiteBishop.setTexture(whiteBishopTexture);
    whiteQueen.setTexture(whiteQueenTexture);
    whiteKing.setTexture(whiteKingTexture);
    
    blackPawn.setTexture(blackPawnTexture);
    blackRook.setTexture(blackRookTexture);
    blackKnight.setTexture(blackKnightTexture);
    blackBishop.setTexture(blackBishopTexture);
    blackQueen.setTexture(blackQueenTexture);
    blackKing.setTexture(blackKingTexture);
}


void GameGraphics::setScale()
{
    sf::FloatRect board = chessboard.getGlobalBounds();
    
    // I assume all pieces files have the same resolution and are squares
    sf::FloatRect piece = blackRook.getGlobalBounds();
    chessboardSize = board.width;
    float scale = (board.width / 8.0) / piece.width;
    
    // hopefully all pieces are the same
    pieceSize = piece.width * scale;

    whitePawn.setScale(scale, scale);
    whiteRook.setScale(scale, scale);
    whiteKnight.setScale(scale, scale);
    whiteBishop.setScale(scale, scale);
    whiteQueen.setScale(scale, scale);
    whiteKing.setScale(scale, scale);
    
    blackPawn.setScale(scale, scale);
    blackRook.setScale(scale, scale);
    blackKnight.setScale(scale, scale);
    blackBishop.setScale(scale, scale);
    blackQueen.setScale(scale, scale);
    blackKing.setScale(scale, scale);

    picked.setSize(sf::Vector2f(scale * chessboardSize, scale * chessboardSize));
    legalMove.setRadius(scale * 150.f);

    circleOffset = 0.125 * 400 - 150.f * 0.125;

}


GameGraphics::GameGraphics()
{
    if (!loadGameTextures())
    {
        std::cout << "Unable to load textures" << std::endl;
        return;
    }

    picked.setPosition(800.f, 800.f);
    picked.setFillColor(sf::Color::Green);

    legalMove.setPosition(300.f, 300.f);
    legalMove.setFillColor(sf::Color(0,200,0,150));

    setTextures();
    setScale();
    return;
}
