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
        }
    }

    if (secondPos.file == firstPos.file && secondPos.rank == firstPos.rank)
    {
        secondClick = false;
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


void GameGraphics::drawChessboard(sf::RenderWindow* const window) const
{
    window->draw(chessboard);
}

void GameGraphics::drawPosition(sf::RenderWindow* const window, Position* const pos)
{
    drawChessboard(window);

    bitboard temp {1};
    sf::Sprite* tempDraw;

    // for all pieces white and black
    for (size_t index {0}; index < 12; index++)
    {
        tempDraw = shareSprite(index);
        // for all squares
        for (size_t i {0}; i < 64; i++)
        {
            // if piece is at given square
            if (pos->pieces.at(index) & (temp << i))
            {
                tempDraw->setPosition(pieceSize * (i % 8), pieceSize * (7 - (i / 8)));
                window->draw(*tempDraw);
            }
        }
    }
}


void GameGraphics::getLegalMoves(Position* const pos)
{
    for (int rank {0}; rank < 8; rank++)
    {
        for (int file {0}; file < 8; file++)
        {
            if (pos->isProperPieceMove(firstPos, {rank, file}))
            {
                legalMoves[rank][file] = pos->isMoveLegal(firstPos, {rank, file});
            }
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

    if (pos->end)
    {
        window->draw(checkmate);
    }
}


sf::Sprite GameGraphics::returnSprite(char temp)
{
    int piece {0};        
    switch (temp)
    {
        // white pieces
        case 'P':
            piece = wPawn;
            break;
        case 'R':
            piece = wRook;
            break;
        case 'N':
            piece = wKnight;
            break;
        case 'B':
            piece = wBishop;
            break;
        case 'Q':
            piece = wQueen;
            break;
        case 'K':
            piece = wKing;
            break;
        
        // black pieces
        case 'p':
            piece = bPawn;
            break;
        case 'r':
            piece = bRook;
            break;
        case 'n':
            piece = bKnight;
            break;
        case 'b':
            piece = bBishop;
            break;
        case 'q':
            piece = bQueen;
            break;
        case 'k':
            piece = bKing;
            break;
        
        // no piece
        case '\0':
            piece = wKing;
            break;
        default:
            piece = bKing;
            break;
        }

    return piecesSprites.at(piece);
}


sf::Sprite* GameGraphics::shareSprite(size_t temp)
{
    int piece = wKing;        
    switch (temp)
    {
        // white pieces
        case 0:
            return &whitePawn;
        case 1:
            return &whiteRook;
        case 2:
            return &whiteKnight;
        case 3:
            return &whiteBishop;
        case 4:
            return &whiteQueen;
        case 5:
            return &whiteKing;
        
        // black pieces
        case 6:
            return &blackPawn;
        case 7:
            return &blackRook;
        case 8:
            return &blackKnight;
        case 9:
            return &blackBishop;
        case 10:
            return &blackQueen;
        case 11:
            return &blackKing;
        
        // no piece
        case 12:
            return &whiteKing;
        default:
            piece = bKing;
            break;
        }

    return &piecesSprites.at(piece);
}


bool GameGraphics::loadGameTextures()
{
    std::string textureDir {"textures/"};
    std::array<std::string, 12> pieceTexture 
    {
        "wPawn.png",
        "wRook.png",
        "wKnight.png",
        "wBishop.png",
        "wQueen.png",
        "wKing.png",
        "bPawn.png",
        "bRook.png",
        "bKnight.png",
        "bBishop.png",
        "bQueen.png",
        "bKing.png"
    };

    if (!chessboardTexture.loadFromFile("textures/chessboard.png"))
    {
        return false;
    }

    for (size_t i {0}; i < piecesTextures.size(); i++)
    {
        if (!piecesTextures.at(i).loadFromFile(textureDir + pieceTexture.at(i)))
        {
            std::cerr << "Failed to load a texture " << (textureDir + pieceTexture.at(i)) << std::endl;
            return false;
        }
    }
    
    return true;
}


void GameGraphics::setTextures()
{
    for (size_t i {0}; i < piecesTextures.size(); i++)
    {
        piecesTextures.at(i).setSmooth(true);
    }

    chessboard.setTexture(chessboardTexture);

    for (size_t i {0}; i < piecesSprites.size(); i++)
    {
        piecesSprites.at(i).setTexture(piecesTextures.at(i));
    }
}

void GameGraphics::setScale()
{
    sf::FloatRect board = chessboard.getGlobalBounds();
    
    // I assume all pieces files have the same resolution and are squares
    sf::FloatRect piece = piecesSprites.at(0).getGlobalBounds();
    chessboardSize = board.width;
    float scale = (board.width / 8.0) / piece.width;
    
    // hopefully all pieces are the same size
    pieceSize = piece.width * scale;

    for (size_t i {0}; i < piecesSprites.size(); i++)
    {
        piecesSprites.at(i).setScale(scale, scale);
    }

    picked.setSize(sf::Vector2f(scale * chessboardSize, scale * chessboardSize));
    checkmate.setSize({board.width, board.width});

    float radius {150.f};
    legalMove.setRadius(scale * radius);

    circleOffset = (400 - radius) * scale;
}


GameGraphics::GameGraphics()
{
    if (!loadGameTextures())
    {
        std::cout << "Unable to load textures" << std::endl;
        return;
    }

    sf::Color highlighter {0,200,0,150};

    checkmate.setFillColor({150, 150, 150, 150});
    checkmate.setPosition(0.f, 0.f);

    picked.setPosition(800.f, 800.f);
    picked.setFillColor(highlighter);

    legalMove.setFillColor(highlighter);

    setTextures();
    setScale();
    return;
}
