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
	float highestPower = 8; //nanti berubah
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


		float mouseRelative = std::abs(mousePos.x - ballStartX);
		float mouseLimit = (wallLength / 2.0 * ((mousePos.y - ballStartY) / (wallY - ballStartY)));
		if (mousePos.y >= ballStartY && mousePos.y <= wallY && mouseRelative < mouseLimit) {

			//!! HARUSE LINKED LIST BOLAE MANTEP	

			//limit jadi cuma bisa nembak ke wall
			if (mouseClicked) {
				//lek nembak
				int ballIndex = 0;
				int placeOffset = 0;
				float tempX = ballStartX + ((mousePos.x - ballStartX) * (wallY - ballStartY) / (mousePos.y - ballStartY)); //projeksi ke dinding
				if (balls.GetSize() > 0) {
					//kalo linkedlist gak kosong
					if (tempX < balls.GetHead()->getPositionX()) {
						//kalo nembaknya di paling kiri
						ballIndex = 10 - std::ceil(balls.GetSize() / 2.0f);
						newball->setPositionIndex(ballIndex);
						for(int i = 0; i < balls.GetSize(); i++)
						{
							balls.GetBall(i)->setPositionIndex(++ballIndex);
						}
						balls.AddFront(newball);
						if (balls.GetSize() % 2 == 0) {
							//kalo genap biar center
							placeOffset = ballRadius;
						}
					}
					else if (tempX > balls.GetTail()->getPositionX())
					{
						//kalo nembaknya di paling kanan
						ballIndex = 10 + std::ceil(balls.GetSize() / 2.0f);
						newball->setPositionIndex(ballIndex);
						ballIndex -= balls.GetSize();
						for (int i = 0; i < balls.GetSize(); i++)
						{
							balls.GetBall(i)->setPositionIndex(ballIndex++);
						}
						balls.AddBack(newball);
						if (balls.GetSize() % 2 == 0) {
							//kalo genap biar center
							placeOffset = -ballRadius;
						}
					}
					else {
						for (int i = 0; i < balls.GetSize() - 1; i++)
						{
							if (balls.GetBall(i)->getPositionX() < tempX && balls.GetBall(i + 1)->getPositionX() >= tempX) {
								if (balls.GetBall(i)->getPositionIndex() < 10) {
									std::cout << "left" << "\n";
									//kalo dikirie tengah
									balls.AddMiddle(i, newball);
									ballIndex = 10 - std::ceil(balls.GetSize() / 2.0f);

									for (int i = 0; i < balls.GetSize(); i++)
									{
										balls.GetBall(i)->setPositionIndex(++ballIndex);
									}
									if (balls.GetSize() % 2 == 0) {
										//kalo genap biar center
										placeOffset = -ballRadius;
									}
								}
								else {
									std::cout << "right" << "\n";
									//kalo di kanan e tengah
									balls.AddMiddle(i, newball);
									ballIndex = 10 + balls.GetSize() / 2.0f + 1;
									ballIndex -= balls.GetSize();
									for (int i = 0; i < balls.GetSize(); i++)
									{
										balls.GetBall(i)->setPositionIndex(ballIndex++);
									}
									if (balls.GetSize() % 2 == 0) {
										//kalo genap biar center
										placeOffset = -ballRadius;
									}
								}
								break;
							}
						}


					}

				}
				else {
					//bola pertama selalu di tengah
					ballIndex = 10;
					newball->setPositionIndex(ballIndex);
					balls.AddBack(newball);
				}

				for (int i = 0; i < balls.GetSize(); i++) //loop e buat draw, kudue loop linked list
				{
					cout << balls.GetBall(i)->getPositionIndex() << " ";
					float newPosOnWallX = wallX - wallLength / 2.0f + placeOffset + balls.GetBall(i)->getPositionIndex() * ballRadius * 2;
					float newPosOnWallY = wallY - ballRadius - wallThickness / 2.0f;
					balls.GetBall(i)->moveTo(sf::Vector2f(newPosOnWallX, newPosOnWallY));

				}
				cout << "\n";

				//proses nggabungno bola



				if (balls.GetSize() == 21) {
					cout << "gameover";
					return 0;
				}

				newball = new Ball(font, sf::Vector2f(ballStartX, ballStartY), ballSpeed, ballRadius, highestPower); // buat bola baru
			}
			arrowPointer.update(mousePos);
		}
		for (int i = 0; i < balls.GetSize(); i++) //loop e buat draw, kudue loop linked list
		{
			balls.GetBall(i)->update(deltaTime);
			balls.GetBall(i)->draw(window);
		}
		newball->update(deltaTime);
		newball->draw(window);
		arrowPointer.draw(window);
		wall.draw(window);
		window.display();

	}

	return 0;
}