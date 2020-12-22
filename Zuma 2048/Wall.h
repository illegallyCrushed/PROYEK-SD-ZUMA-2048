#pragma once
#include "includes.h"
class Wall
{
public:
	Wall(sf::Vector2f size, sf::Vector2f position);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape wall;

};
