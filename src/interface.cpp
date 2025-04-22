#include <iostream>
#include "interface.h"
#include "gameLogic.h"


sf::Sprite GameGraphics::returnSprite(size_t temp)
{
    return piecesSprites.at(temp);
}


sf::Sprite* GameGraphics::shareSprite(size_t temp)
{
    return &(piecesSprites.at(temp));
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

void Interface::drawPosition(sf::RenderWindow* const window, Position* const pos)
{
    window->draw(g.chessboard);
    window->draw(g.picked);

    bitboard temp {1};
    sf::Sprite* tempDraw;

    // for all pieces white and black
    for (size_t index {0}; index < 12; index++)
    {
        tempDraw = g.shareSprite(index);
        // for all squares
        for (size_t i {0}; i < 64; i++)
        {
            // if piece is at given square
            if (pos->pieces.at(index) & (temp << i))
            {
                tempDraw->setPosition(g.pieceSize * (i % 8), g.pieceSize * (7 - (i / 8)));
                window->draw(*tempDraw);
            }
        }
    }

    drawLegalMoves(window);

    if (pos->end)
    {
        window->draw(g.checkmate);
    }
}


void Interface::drawLegalMoves(sf::RenderWindow* const window)
{
    if (!legalMoves)
    {
        return;
    }

    // white side
    bitboard temp {1};
    for (size_t i {0}; i < 64; i++, temp <<= 1)
    {
        if (legalMoves & temp)
        {
            g.legalMove.setPosition((i % 8) * g.pieceSize + g.circleOffset, (7 - (i / 8)) * g.pieceSize + g.circleOffset);
            window->draw(g.legalMove);
        }
    }

}


void Interface::leftMouseInteract(sf::RenderWindow* const window, Position* const curr)
{
    mouseF = window->mapPixelToCoords(mouse);
    if (g.board.contains(mouseF))
    {
        if (firstClick == false)
        {
            firstClick = true;
            firstPos.file = mouse.x / 100.f;
            firstPos.rank = 7 - mouse.y / 100.f + 1;
            g.picked.setPosition(firstPos.file * g.pieceSize, (7 - firstPos.rank) * g.pieceSize);
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
            g.picked.setPosition(firstPos.file * g.pieceSize, (7 - firstPos.rank) * g.pieceSize);
        }
        g.picked.setPosition({g.chessboardSize, g.chessboardSize});
        resetLegalMoves();
    }
}


void Interface::getLegalMoves(Position* const pos)
{
    legalMoves = pos->legalMoves(firstPos);
}


void Interface::resetLegalMoves()
{
    legalMoves = 0;
}


void Interface::resetPicked()
{
    firstClick = false;
    secondClick = false;
    g.picked.setPosition(g.chessboardSize, g.chessboardSize);
    resetLegalMoves();
}
