#include "SLL.h"

SLL::SLL()
{
	Head = Tail = NULL;
	Size = 0;
}

Ball* SLL::GetHead()
{
	return Head;
}

Ball* SLL::GetTail()
{
	return Tail;
}

int SLL::GetSize()
{
	return Size;
}

void SLL::AddFront(Ball *ball)
{
	Ball* temp = ball;
    temp->SetNext(Head);
    Head = temp;
	Size++;
}

void SLL::AddMiddle(int index, Ball *ball)
{
	Ball* temp = ball;
	temp->SetNext(NULL);

	Ball* iteration = Head;

	for (int i = 0; i < index; i++)
		iteration = iteration->GetNext();

	temp->SetNext(iteration->GetNext());
	iteration->SetNext(temp);
	Size++;
}

void SLL::AddBack(Ball *ball)
{
	Ball* temp = ball;
	temp->SetNext(NULL);

	if (Head == NULL) {
		Head = temp;
		Tail = temp;
	}
	else {
		Tail->SetNext(temp);
		Tail = temp;
	}
	Size++;
}

void SLL::Delete(int index)
{
	if (index >= Size)
		return;

	Ball* temp = Head;

	if (index == 0) {
		temp = temp->GetNext();
		Head = temp;
	}
	else if (index == Size - 1) {
		for (int i = 0; i < Size; i++)
			temp = temp->GetNext();

		temp->SetNext(NULL);
	}
	else {
		for (int i = 0; i < index; i++)
			temp = temp->GetNext();

		temp->SetNext(temp->GetNext()->GetNext());
	}
	delete temp;
	Size--;
}

void SLL::Edit(int index, int n)
{
	if (index >= Size)
		return;

	Ball* iteration = Head;

	for (int i = 0; i < index; i++)
		iteration = iteration->GetNext();

	iteration->SetNumber(n);
}

void SLL::DeleteCombo(int start, int end)
{
	if (start < 0 || start >= Size || end < 0 || end >= Size)
		return;

	for (int i = start; i <= end; i++)
		Delete(i);
}

Ball* SLL::GetBall(int index)
{
	Ball* iteration = Head;
	for (int i = 0; i < index; i++) {
		iteration = iteration->GetNext();
	}
	return iteration;
}

<<<<<<< Updated upstream
void SLL::drawAll(sf::RenderWindow &window)
{
	Ball* iter = Head;
	while (iter != NULL){
		iter->draw(window);
		iter = iter->GetNext();
	}
}

void SLL::updateAll()
{
	Ball* iter = Head;
	while (iter != NULL) {
		iter->update();
		iter = iter->GetNext();
	}
}

void SLL::resyncPosition(float xOffset, float yOffset, float ballRadius)
{
	int ballIndex = 10 - Size / 2;
	int placeOffset = 0;
	if (Size % 2 == 0) {
		placeOffset = ballRadius;
	}
	Ball* iter = Head;
	while (iter != NULL)
	{
		iter->setPositionIndex(ballIndex++);
		float newPosOnWallX = xOffset + placeOffset + iter->getPositionIndex() * ballRadius * 2;
		float newPosOnWallY = yOffset - ballRadius;
		iter->moveTo(sf::Vector2f(newPosOnWallX, newPosOnWallY));
		iter = iter->GetNext();
	}

=======
void SLL::CheckCombo(SLL& balls)
{
	Ball* iterator = balls.GetHead();
	Ball* iteratordalam = iterator;
	int counter = 0;
	int countercombo = 0;

	if (balls.GetSize() >= 4) {
		while (iterator->GetNext() != NULL) {
			while (iteratordalam->GetNext() != NULL && countercombo <= 4) {
				if(iteratordalam->GetColor() == iteratordalam->GetNext()->GetColor() && iteratordalam->GetNumber() == iteratordalam->GetNext()->GetNumber()) {
					counter++;
				}
				if (counter == 4) {
					balls.DeleteCombo(iterator->getPositionIndex(), iterator->getPositionIndex() + 2);
					cout << "COMBOOOO!!!\n";
				}
				iteratordalam = iteratordalam->GetNext();
				countercombo++;
			}
			countercombo = 0;
			counter = 0;
			iterator = iterator->GetNext();
			iteratordalam = iterator;
		}
	}

	
>>>>>>> Stashed changes
}
