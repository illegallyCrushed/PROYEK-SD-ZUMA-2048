#include "Arrow.h"

Arrow::Arrow(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position)
{
	arrowRect.setSize(size);
	arrowRect.setTexture(texture);
	arrowRect.setOrigin(arrowRect.getSize().x/2,arrowRect.getSize().y/2);
	arrowRect.setPosition(position);
}

void Arrow::update(float deltaTime, sf::Vector2i mousePos)
{

}

void Arrow::draw(sf::RenderWindow& window)
{
	window.draw(arrowRect);
}
