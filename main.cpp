#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "gameLogic.h"
#include "interface.h"


int main()
{
    GameGraphics ui;
    Position curr {};       // turn this into a pointer in the future
                            // "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    ui.loadGameTextures();
    ui.setTextures();

    sf::RenderWindow window(sf::VideoMode(ui.WWIDTH, ui.WHEIGHT), "Chess", sf::Style::Close);


    while (window.isOpen())
    {
        ui.drawChessboard(&window);
        ui.mouse = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                ui.resetPicked();
                std::cout << curr.returnFEN() << std::endl;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                ui.leftMouseInteract(&window, &curr);
            }
        }

        window.draw(ui.picked);
        ui.drawPosition(&window, &curr);
        ui.drawLegalMoves(&window, &curr);
        if (curr.end)
        {
            window.draw(ui.checkmate);
        }

        window.display();
        window.clear();
    }

    return 0;
}
