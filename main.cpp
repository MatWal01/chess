#include <iostream>
#include <SFML/Graphics.hpp>
#include "interface.h"
#include "gameLogic.h"

const int windowHeight {800};
const int windowWidth {800};


int main()
{
    GameGraphics ui;
    ui.loadGameTextures();
    ui.setTexture();

    Position curr;
    curr.setPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chess", sf::Style::Close);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(ui.chessboard);

        // draw from the perspective of white
        for (int i {7}; i >= 0; i--)
        {
            for (size_t j {0}; j < 8; j++)
            {
                Piece temp = curr.getPiece(i, j);
                if (temp.pieceSymbol == '\0')
                {
                    continue;
                }

                sf::Sprite tempDraw = ui.returnSprite(temp);
                tempDraw.move(ui.pieceSize * i, ui.pieceSize * (7 - j));
                window.draw(tempDraw);
            }
        }
        window.display();
    }

    return 0;
}
