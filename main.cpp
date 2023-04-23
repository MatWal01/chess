#include <SFML/Graphics.hpp>

const int windowHeight {800};
const int windowWidth {800};



int main()
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
    sf::Texture chessBoard;
    if (!chessBoard.loadFromFile("textures/chessboard.png"))
    {
        return 1;
    }

    sf::Sprite board;
    board.setTexture(chessBoard);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(board);
        window.display();
    }

    return 0;
}
