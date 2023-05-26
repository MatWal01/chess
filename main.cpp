#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "interface.h"
#include "gameLogic.h"

const int WINDOWHEIGHT {800};
const int WINDOWWIDTH {800};


int main()
{
    GameGraphics ui;
    Position curr;      // turn this into a pointer in the future
    ui.loadGameTextures();
    ui.setTextures();
    curr.setPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");


    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Chess", sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        curr.drawPosition(&window, &ui);
        window.display();
    }

    return 0;
}
