#include "Ball.h"

Ball::Ball(sf::Font& font, sf::Vector2f position, float speed, float radius, int powernumber)
{
	sf::Color colors[4] = { sf::Color::Red, sf::Color::Green, sf::Color::Cyan, sf::Color::Yellow };

	color = rand() % 4;
	power = (1 + (rand() % (powernumber - 1)));
	number = std::pow(2, power);

	this->speed = speed;
	newposition = position;

	circle.setRadius(radius);
	circle.setFillColor(colors[color]);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(position);

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

void Ball::moveTo(sf::Vector2f newposition)
{
	this->newposition = newposition;
}

bool Ball::update()
{
	circle.setPosition(circle.getPosition().x + (newposition.x - circle.getPosition().x) * speed, circle.getPosition().y + (newposition.y - circle.getPosition().y) * speed);
	textnum.setPosition(textnum.getPosition().x + (newposition.x - textnum.getPosition().x) * speed, textnum.getPosition().y + (newposition.y - textnum.getPosition().y) * speed);
	if (std::abs(newposition.x - circle.getPosition().x) < 1 && std::abs(newposition.y - circle.getPosition().y) < 1) {
		circle.setPosition(newposition);
		textnum.setPosition(newposition);
		return true;
	}
	return false;
}


void Ball::draw(sf::RenderWindow& window)
{
	window.draw(circle);
	window.draw(textnum);
}

float Ball::getPositionX()
{
	return newposition.x;
}

int Ball::getPositionIndex()
{
	return posIndex;
}

void Ball::setPositionIndex(int index)
{
	posIndex = index;
}

Ball* Ball::GetNext()
{
	return Next;
}

void Ball::SetNext(Ball* ball)
{
	Next = ball;
}

void Ball::SetNumber(int n)
{
	number = n;
	textnum.setString(std::to_string(number));
	textnum.setCharacterSize(30);
	textnum.setOrigin((textnum.getLocalBounds().width / 2.0f) + 2, (textnum.getLocalBounds().height / 2.0f) + 9.5);
	if (number >= 1024) {
		textnum.setCharacterSize(20);
		textnum.setOrigin((textnum.getLocalBounds().width / 2.0f), (textnum.getLocalBounds().height / 2.0f) + 6.5);
	}
	textnum.setPosition(circle.getPosition());
}

int Ball::GetNumber()
{
	return number;
}

int Ball::GetColor()
{
	return color;
}
