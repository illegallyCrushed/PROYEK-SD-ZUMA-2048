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

void SLL::AddFront(Ball* ball)
{
	Ball* temp = ball;
	temp->SetNext(Head);
	Head = temp;
	Size++;
}

void SLL::AddMiddle(int index, Ball* ball)
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

void SLL::AddBack(Ball* ball)
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
		Head = temp->GetNext();
		delete temp;
	}
	else if (index == Size - 1) {
		for (int i = 0; i < Size - 1; i++)
			temp = temp->GetNext();
		Ball* temp2 = temp->GetNext();
		temp->SetNext(NULL);
		Tail = temp;
		delete temp2;
	}
	else {
		for (int i = 0; i < index - 1; i++)
			temp = temp->GetNext();
		Ball* temp2 = temp->GetNext();
		temp->SetNext(temp2->GetNext());
		delete temp2;
	}
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

void SLL::drawAll(sf::RenderWindow& window)
{
	Ball* iter = Head;
	while (iter != NULL) {
		iter->draw(window);
		iter = iter->GetNext();
	}
}

bool SLL::updateAll()
{
	bool allDone = true;
	Ball* iter = Head;
	while (iter != NULL) {
		if (!iter->update())
			allDone = false;
		iter = iter->GetNext();
	}
	return allDone;
}

void SLL::resyncPosition(float xOffset, float yOffset, float ballRadius,int maxBall)
{
	int ballIndex = maxBall/2 - Size / 2;
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
}

bool SLL::CheckCombo(SLL& balls)
{
	int indexiterator = 0;
	bool deleted = false;

	if (balls.GetSize() >= 4) {
		Ball* iterator = balls.GetHead();
		while (iterator != NULL)
		{
			int currentcolor = iterator->GetColor();
			int currentnumber = iterator->GetNumber();
			int counter = 0;
			Ball* iterator2 = iterator;
			while (iterator2 != NULL)
			{
				if (currentcolor == iterator2->GetColor() && currentnumber == iterator2->GetNumber()) {
					counter++;
					if (counter == 4) {
						for (int i = 0; i < 3; i++) {
							balls.Delete(indexiterator);
						}
						balls.Edit(indexiterator, currentnumber * 2);
						deleted = true;
						break;
					}
				}
				else {
					break;
				}
				if (iterator2->GetNext() == NULL) {
					break;
				}
				iterator2 = iterator2->GetNext();
			}
			if (deleted) {
				break;
			}
			iterator = iterator->GetNext();
			indexiterator++;

		}
	}
	return deleted;
}

int SLL::CheckPowerNumber(SLL& balls)
{
	int max = 0;
	Ball* iterator = balls.GetHead();

	for (int i = 0; i < balls.GetSize(); i++) {
		if (iterator->GetNumber() > max) {
			max = iterator->GetNumber();
		}
	}
	
	return std::log2(max);
}
