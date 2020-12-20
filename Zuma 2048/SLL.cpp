#include "SLL.h"

Node::Node(int data, string color) {
	Data = data; Color = color; Next = NULL;
}

void Node::SetData(int data)
{
	Data = data;
}

void Node::SetColor(string color)
{
	Color = color;
}

void Node::SetNext(Node* next)
{
	Next = next;
}

int Node::GetData()
{
	return Data;
}

string Node::GetColor()
{
	return Color;
}

Node* Node::GetNext()
{
	return Next;
}

SLL::SLL()
{
	Head = Tail = NULL;
	Size = 0;
}

Node* SLL::GetHead()
{
	return Head;
}

int SLL::GetSize()
{
	return Size;
}

void SLL::AddFront(int n, string color)
{
	if (Size == MaxSize)
		return;

    Node* temp = new Node;
    temp->SetData(n);
	temp->SetColor(color);
    temp->SetNext(Head);
    Head = temp;
	Size++;
}

void SLL::AddMiddle(int index, int n, string color)
{
	if (Size == MaxSize)
		return;

	Node* temp = new Node;
	temp->SetData(n);
	temp->SetColor(color);
	temp->SetNext(NULL);

	Node* iteration = Head;

	for (int i = 0; i < index; i++)
		iteration = iteration->GetNext();

	temp->SetNext(iteration->GetNext());
	iteration->SetNext(temp);
	Size++;
}

void SLL::AddBack(int n, string color)
{
	if (Size == MaxSize)
		return;

	Node* temp = new Node;
	temp->SetData(n);
	temp->SetColor(color);
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

	Node* temp = Head;

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

	Node* iteration = Head;

	for (int i = 0; i < index; i++)
		iteration = iteration->GetNext();

	iteration->SetData(n);
}

void SLL::DeleteCombo(int start, int end)
{
	if (start < 0 || start >= Size || end < 0 || end >= Size)
		return;

	for (int i = start; i <= end; i++)
		Delete(i);
}
