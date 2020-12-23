#include "Ball.h"
#include "SLL.h"
#include "Arrow.h"
#include "Wall.h"

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Zuma 2048", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Vector2i mousePos;

	SLL balls;
	sf::Font font;
	sf::Texture arrowtexture;
	font.loadFromFile("Assets/Google Product Sans.ttf");
	arrowtexture.loadFromFile("Assets/arrow.png");

	float ballStartX = WINDOW_WIDTH / 2;
	float ballStartY = WINDOW_HEIGHT / 6;
	float ballRadius = 24;
	float maxBall = 26;
	float highestPower = 2;
	float ballSpeed = 0.2;

	float wallX = WINDOW_WIDTH / 2;
	float wallY = WINDOW_HEIGHT * 7 / 8;
	float wallLength = maxBall * ballRadius * 2;
	float wallThickness = 10;

	float toggleClickTime = 0.0f;
	float deltaTime = 0;
	bool stage1 = false;
	bool stage2 = false;
	bool stage3 = false;
	bool stage4 = false;
	bool mouseClicked = false;
	bool clickAllowed = true;

	Arrow arrowPointer(&arrowtexture, sf::Vector2f(1000, 1000), sf::Vector2f(ballStartX, ballStartY));
	Wall wall(sf::Vector2f(wallLength, wallThickness), sf::Vector2f(wallX, wallY));

	Ball* newball = new Ball(font, sf::Vector2f(ballStartX, ballStartY), ballSpeed, ballRadius, highestPower);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		mouseClicked = false;
		window.clear(sf::Color(30, 30, 30));
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved)
				mousePos = sf::Mouse::getPosition(window);
			if (clickAllowed) {
				if (event.type == sf::Event::MouseButtonPressed) {
					mouseClicked = true;
					clickAllowed = false;
				}
			}
		}

		if (mouseClicked) {
			stage1 = true;

			float xOffset = wallX - wallLength / 2.0f;
			float yOffset = wallY - wallThickness / 2.0f;
			float tempX = ballStartX + ((mousePos.x - ballStartX) * (wallY - ballStartY) / (mousePos.y - ballStartY)); //projeksi ke dinding
			if (balls.GetSize() > 0) {
				//kalo linkedlist tidak kosong
				if (tempX < balls.GetHead()->getPositionX()) {
					//kalo nembaknya di paling kiri
					balls.AddFront(newball);
				}
				else if (tempX > balls.GetTail()->getPositionX())
				{
					//kalo nembaknya di paling kanan
					balls.AddBack(newball);
				}
				else {
					//kalo nembaknya ditengah
					int i = 0;
					Ball* iter = balls.GetHead();
					while (iter->GetNext() != NULL)
					{
						if (iter->getPositionX() < tempX && iter->GetNext()->getPositionX() >= tempX) {
							balls.AddMiddle(i, newball);
							break;
						}
						i++;
						iter = iter->GetNext();
					}
				}
			}
			else {
				balls.AddBack(newball);
			}
			balls.resyncPosition(xOffset, yOffset, ballRadius, maxBall);

			

			newball = new Ball(font, sf::Vector2f(ballStartX, ballStartY), ballSpeed, ballRadius, highestPower); // buat bola baru
		}

		if (stage1) {
			if (balls.updateAll()) {
				stage1 = false;
				stage2 = true;
			}
		}

		if (stage2) {
			float xOffset = wallX - wallLength / 2.0f;
			float yOffset = wallY - wallThickness / 2.0f;
			bool available = balls.CheckCombo(balls);
			//proses penggabungan bola
			balls.resyncPosition(xOffset, yOffset, ballRadius, maxBall);

			//check power number
			
			if (available) {
				//buat multiple combos
				stage2 = false;
				stage3 = true;
			}
			else {
				//kalo tidak ketemu
				stage2 = false;
				stage3 = false;
				stage4 = true;
			}
		}

		if (stage3) {
			//multiple combos, balik ke stage 2
			if (balls.updateAll()) {
				stage2 = true;
				stage3 = false;
			}
		}

		if (stage4) {
			//tidak ketemu multiple combos, ngecek kkalah enable click
			if (balls.GetSize() == maxBall + 1) {
				cout << "Gameover\n";
				system("pause");
				return 0;
			}
			if (balls.updateAll()) {
				stage1 = false;
				stage2 = false;
				stage3 = false;
				stage4 = false;
				clickAllowed = true;
			}
		}

		if (balls.GetSize() > 0 && balls.CheckPowerNumber(balls) >= 2) {
			highestPower = balls.CheckPowerNumber(balls);
		}

		float mouseRelative = std::abs(mousePos.x - ballStartX);
		float mouseLimit = (wallLength / 1.5 * ((mousePos.y - ballStartY) / (wallY - ballStartY)));
		if (mousePos.y >= ballStartY && mouseRelative < mouseLimit) {
			arrowPointer.update(mousePos);
		}

		balls.drawAll(window);
		newball->update();
		newball->draw(window);
		arrowPointer.draw(window);
		wall.draw(window);
		window.display();
	}
	return 0;

}