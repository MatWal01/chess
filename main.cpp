#include <SFML/Graphics.hpp>
#include "interface.h"

const int windowHeight {800};
const int windowWidth {800};


int main()
{
    GameGraphics ui;
    ui.loadInterfaceTextures();
    ui.setTexture();

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
        window.draw(ui.blackRook);
        window.display();
    }

    return 0;
}
