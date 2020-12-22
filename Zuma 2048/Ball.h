#pragma once
#include "includes.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Ball
{
public:
	Ball();
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
private:
	sf::Vector2f position;
	sf::Vector2f delta;
	sf::CircleShape circle;
	sf::Text num;
};
