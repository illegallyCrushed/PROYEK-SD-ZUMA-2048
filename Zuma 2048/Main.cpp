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
	float deltaTime = 0;
	sf::Vector2i mousePos;
	bool mouseClicked = false;
	bool clickAllowed = true;
	float toggleClickTime = 0.0f;
	SLL balls; //iki di linkedlist
	sf::Font font;
	sf::Texture arrowtexture;
	font.loadFromFile("Assets/Google Product Sans.ttf");
	arrowtexture.loadFromFile("Assets/arrow.png");

	float ballStartX = WINDOW_WIDTH / 2;
	float ballStartY = WINDOW_HEIGHT / 6;
	float ballRadius = 25;
	float maxBall = 20;
	float highestPower = 2; //nanti berubah
	float ballSpeed = 0.1;

	float wallX = WINDOW_WIDTH / 2;
	float wallY = WINDOW_HEIGHT * 7 / 8;
	float wallLength = maxBall * ballRadius * 2;
	float wallThickness = 10;


	Arrow arrowPointer(&arrowtexture, sf::Vector2f(1000, 1000), sf::Vector2f(ballStartX, ballStartY));
	Wall wall(sf::Vector2f(wallLength, wallThickness), sf::Vector2f(wallX, wallY));


	Ball* newball = new Ball(font, sf::Vector2f(ballStartX, ballStartY), ballSpeed, ballRadius, highestPower);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		mouseClicked = false;
		window.clear();
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


		if (!clickAllowed) {

			//nyoba
			toggleClickTime += deltaTime;
			if (toggleClickTime >= 0.05) {
				clickAllowed = true;
				toggleClickTime = 0;
			}

		}






		if (mouseClicked) {
			//lek nembak
			float xOffset = wallX - wallLength / 2.0f;
			float yOffset = wallY - wallThickness / 2.0f;
			float tempX = ballStartX + ((mousePos.x - ballStartX) * (wallY - ballStartY) / (mousePos.y - ballStartY)); //projeksi ke dinding
			if (balls.GetSize() > 0) {
				//kalo linkedlist gak kosong
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
			balls.resyncPosition(xOffset, yOffset, ballRadius);

			//proses nggabungno bola


			if (balls.GetSize() == 21) {
				cout << "gameover";
				return 0;
			}

			newball = new Ball(font, sf::Vector2f(ballStartX, ballStartY), ballSpeed, ballRadius, highestPower); // buat bola baru
		}

		float mouseRelative = std::abs(mousePos.x - ballStartX);
		float mouseLimit = (wallLength / 1.5 * ((mousePos.y - ballStartY) / (wallY - ballStartY)));
		if (mousePos.y >= ballStartY && mouseRelative < mouseLimit) {
			arrowPointer.update(mousePos);


			balls.updateAll();
			balls.drawAll(window);
			newball->update();
			newball->draw(window);
			arrowPointer.draw(window);
			wall.draw(window);
			window.display();

		}
	}
	return 0;

}