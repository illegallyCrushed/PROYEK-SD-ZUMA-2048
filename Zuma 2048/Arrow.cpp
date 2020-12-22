#include "Arrow.h"

Arrow::Arrow(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	this->position = position;
	arrowRect.setSize(size);
	arrowRect.setTexture(texture);
	arrowRect.setOrigin(arrowRect.getSize().x / 2, arrowRect.getSize().y / 2);
	arrowRect.setPosition(position);
}

void Arrow::update(sf::Vector2i mousePos)
{
	double radianAngle = atan2(mousePos.y + position.y, mousePos.x - position.x);
	double pi = 2 * acos(0.0);
	double degreeAngle = -90 + (radianAngle * (180 / M_PI));
	arrowRect.setRotation(degreeAngle);
	std::cout << "Angle " << radianAngle << " mouseX " << mousePos.x << " posX " << position.x << "  mouseY " << mousePos.y << " posY " << position.y<<"\n";
}

void Arrow::draw(sf::RenderWindow& window)
{
	window.draw(arrowRect);
}
