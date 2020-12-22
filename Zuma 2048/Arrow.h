#pragma once
#include "includes.h"

class Arrow
{
public:
	Arrow(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position);
	void update(sf::Vector2i mousePos);
	void draw(sf::RenderWindow &window);

private:
	sf::RectangleShape arrowRect;
	sf::Vector2f position;
};
