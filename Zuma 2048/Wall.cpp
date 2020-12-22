#include "Wall.h"

Wall::Wall(sf::Vector2f size, sf::Vector2f position)
{
	wall.setFillColor(sf::Color::White);
	wall.setSize(size);
	wall.setOrigin(size.x/2.0f,size.y/2.0f);
	wall.setPosition(position);
}

void Wall::draw(sf::RenderWindow& window)
{
	window.draw(wall);
}
