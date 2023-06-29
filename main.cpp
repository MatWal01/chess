#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "gameLogic.h"
#include "interface.h"


int main()
{
    GameGraphics ui;
    Position curr;      // turn this into a pointer in the future
    ui.loadGameTextures();
    ui.setTextures();
    curr.setPosition("rnbq1bnr/pppppppp/8/3k4/3K4/8/PPPPPPPP/RNBQ1BNR w KQkq - 0 1");


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
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                ui.leftMouseInteract(&window, &curr);
            }
        }

        window.draw(ui.picked);
        ui.drawPosition(&window, &curr);
        ui.drawLegalMoves(&window, &curr);
        window.display();
        window.clear();
    }

    return 0;
}
