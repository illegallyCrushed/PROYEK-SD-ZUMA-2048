#include "Ball.h"
#include "SLL.h"

int main()
{

    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Zuma 2048", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Clock deltaTime;
    sf::Vector2i mousePos;
    bool mouseClicked = false;
    std::vector <Ball> balls;
    sf::Font font;
    font.loadFromFile("Assets/Google Product Sans.ttf");


    balls.push_back(Ball());

    while (window.isOpen())
    {
        deltaTime.restart().asSeconds();
        mouseClicked = false;
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved) 
                mousePos = sf::Mouse::getPosition(window);
            mouseClicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        }



        for (Ball &ball : balls)
        {
            ball.update(deltaTime.getElapsedTime().asSeconds());
            ball.draw(window);
        }
        window.display();
    }

    return 0;
}