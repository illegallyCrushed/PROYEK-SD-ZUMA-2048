#include "Ball.h"

Ball::Ball()
{
	sf::Color colors[4] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };
	position.x = WINDOW_WIDTH / 2;
	position.y = WINDOW_HEIGHT / 6;
	circle.setRadius(25.0f);
	circle.setFillColor(colors[rand()%4]);
	circle.setPosition(position);
	circle.setOrigin(circle.getRadius() / 2, circle.getRadius() / 2);
}

void Ball::update(float deltaTime)
{
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(circle);
}
