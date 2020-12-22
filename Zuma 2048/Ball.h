#pragma once
#include "includes.h"

class Ball
{
public:
	Ball(sf::Font &font, sf::Vector2f position, float speed, float radius, int powernumber);
	void moveTo(sf::Vector2f newposition);
	bool update();
	void draw(sf::RenderWindow &window);
	float getPositionX();
	int getPositionIndex();
	void setPositionIndex(int index);
	Ball *GetNext();
	void SetNext(Ball *ball);
	void SetNumber(int n);
	int GetNumber();
	int GetColor();

private:
	sf::Vector2f newposition;
	sf::CircleShape circle;
	sf::Text textnum;
	int number;
	int color;
	int power;
	int posIndex;
	float speed;
	Ball* Next;
};
