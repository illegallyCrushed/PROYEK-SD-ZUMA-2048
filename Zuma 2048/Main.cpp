#include "Ball.h"
#include "SLL.h"
#include "Arrow.h"

int main()
{

	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Zuma 2048", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Clock clock;
	float deltaTime = 0;
	sf::Vector2i mousePos;
	bool mouseClicked = false;
	bool clickAllowed = true;
	float toggleClickTime = 0.0f;
	std::vector <Ball> balls;
	sf::Font font;
	sf::Texture arrowtexture;
	font.loadFromFile("Assets/Google Product Sans.ttf");
	arrowtexture.loadFromFile("Assets/arrow.png");
	Arrow arrowPointer(&arrowtexture, sf::Vector2f(1000, 1000), sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6));


	balls.push_back(Ball(font, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6), 25.0f, 4));

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		mouseClicked = false;
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved)
				mousePos = sf::Mouse::getPosition(window);
			if (clickAllowed) {
				if (event.type == sf::Event::MouseButtonPressed) {
					mouseClicked = true;
					clickAllowed = false;
				}
			}

		}

		if (mouseClicked) {
			balls.push_back(Ball(font, sf::Vector2f(mousePos.x, mousePos.y), 25.0f, 4));
		}
		if (!clickAllowed) {

			//nyoba
			toggleClickTime += deltaTime;
			cout << toggleClickTime << "\n";
			if (toggleClickTime >= 2) {
				clickAllowed = true;
				toggleClickTime = 0;
			}

		}

		for (Ball& ball : balls)
		{
			ball.update(deltaTime);
			ball.draw(window);
		}
		arrowPointer.update(mousePos);
		arrowPointer.draw(window);
		window.display();

	}

	return 0;
}