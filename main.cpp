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
    curr.setPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");


    sf::RenderWindow window(sf::VideoMode(ui.WWIDTH, ui.WHEIGHT), "Chess", sf::Style::Close);
    sf::Vector2i mouse;
    sf::Vector2f mouseF;

    bool firstClick {false};
    piecePos firstPos {0, 0};
    bool secondClick {false};
    piecePos secondPos {0, 0};
    
    sf::RectangleShape picked;
    picked.setPosition(800.f, 800.f);
    picked.setFillColor(sf::Color::Green);
    picked.setSize(sf::Vector2f(100.f, 100.f));


    while (window.isOpen())
    {
        ui.drawChessboard(&window);
        mouse = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                mouseF = window.mapPixelToCoords(mouse);
                if (ui.board.contains(mouseF))
                {
                    if (firstClick == false)
                    {
                        firstClick = true;
                        firstPos.file = mouse.x / 100;
                        firstPos.rank = 7 - mouse.y / 100;
                        picked.setPosition(firstPos.file * 100.f, (7 - firstPos.rank) * 100.f);
                    }
                    else if(secondClick == false)
                    {
                        secondPos.file = mouse.x / 100;
                        secondPos.rank = 7 - mouse.y / 100;
                        if (secondPos.file == firstPos.file && secondPos.rank == firstPos.rank)
                        {
                            secondClick = false;
                            break;
                        }
                        secondClick = true;
                    }
                }
            }


            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                firstClick = false;
                secondClick = false;
                picked.setPosition(800.f, 800.f);
            }

            if (firstClick == true && secondClick == true)
            {
                firstClick = false;
                secondClick = false;

                if (!curr.movePiece(firstPos, secondPos))
                {
                    firstClick = true;
                    firstPos.file = mouse.x / 100;
                    firstPos.rank = 7 - mouse.y / 100;
                    picked.setPosition(firstPos.file * 100.f, (7 - firstPos.rank) * 100.f);
                }
            }
        }

        window.draw(picked);
        ui.drawPosition(&window, &curr);
        window.display();
        window.clear();
    }

    return 0;
}
