#pragma once
#include "includes.h"

class Ball
{
public:
	Ball(sf::Font &font, sf::Vector2f position, float radius, int powernumber);
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
private:
	sf::Vector2f position;
	sf::Vector2f delta;
	sf::CircleShape circle;
	sf::Text textnum;
	int number;
	int color;
};
