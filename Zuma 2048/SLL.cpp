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
