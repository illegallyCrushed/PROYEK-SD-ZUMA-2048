#include "Ball.h"

Ball::Ball(sf::Font& font, sf::Vector2f position, float radius, int powernumber)
{
	sf::Color colors[4] = { sf::Color::Red, sf::Color::Green, sf::Color::Cyan, sf::Color::Yellow };

	color = rand() % 4;
	number = std::pow(2, (1 + (rand() % (powernumber - 1))));

	this->position = position;
	circle.setRadius(radius);
	circle.setFillColor(colors[color]);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(position);
	std::cout << "Radius " << circle.getRadius() << " " << circle.getRadius();
	std::cout << "Origin " << circle.getOrigin().x << " " << circle.getOrigin().y;
	std::cout << "Position " << circle.getPosition().x << " " << circle.getPosition().y;

	textnum.setFont(font);
	textnum.setString(std::to_string(number));
	textnum.setFillColor(sf::Color::Black);
	textnum.setCharacterSize(30);
	textnum.setOrigin((textnum.getLocalBounds().width / 2.0f) + 2, (textnum.getLocalBounds().height / 2.0f) + 9.5);
	if (number >= 1024) {
		textnum.setCharacterSize(20);
		textnum.setOrigin((textnum.getLocalBounds().width / 2.0f), (textnum.getLocalBounds().height / 2.0f) + 6.5);
	}
	textnum.setPosition(position);
}

void Ball::update(float deltaTime)
{
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(circle);
	window.draw(textnum);
}
