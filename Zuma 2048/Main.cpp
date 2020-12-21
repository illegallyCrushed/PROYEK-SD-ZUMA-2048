#include <SFML/Graphics.hpp>
#include "SLL.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Zuma 2048", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}