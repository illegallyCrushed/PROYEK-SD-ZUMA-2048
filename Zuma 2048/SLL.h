#include <string>
#include "Ball.h"
using namespace std;
#pragma once

class SLL {
private:
	Ball* Head;
	Ball* Tail;
	int Size;
public:
	SLL();
	Ball* GetHead();
	Ball* GetTail();
	int GetSize();
	void AddFront(Ball *ball);
	void AddMiddle(int index, Ball *ball);
	void AddBack(Ball *ball);
	void Delete(int index);
	void Edit(int index, int n);
	void DeleteCombo(int start, int end);
	Ball* GetBall(int index);
};

