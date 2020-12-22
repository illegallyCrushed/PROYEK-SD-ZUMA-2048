#pragma once
#include "includes.h"
using namespace std;

class Node {
private:
	int Data;
	string Color;
	Node* Next;
public:
	Node(int data = 1, string color = "red");
	void SetData (int data = 1);
	void SetColor(string color = "red");
	void SetNext(Node* next);
	int GetData();
	string GetColor();
	Node* GetNext();
};

class SLL {
private:
	Node* Head;
	Node* Tail;
	int MaxSize = 10;
	int Size;
public:
	SLL();
	Node* GetHead();
	int GetSize();
	void AddFront(int n, string color);
	void AddMiddle(int index, int n, string color);
	void AddBack(int n, string color);
	void Delete(int index);
	void Edit(int index, int n);
	void DeleteCombo(int start, int end);
};

