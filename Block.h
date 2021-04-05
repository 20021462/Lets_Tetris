#pragma once
#include "render.h"
#include "const.h"

class Block
{
public:
	enum Block_type
	{
		Z=1,
		S,
		J,
		L,
		O,
		I,
		T,
	};

	Block(int type);
	~Block();

	void move(int x, int y);
	void rotate(int matrix[4][4]=NULL);
	bool collide();
	void gravity();
	void print();

	int x();
	int y();
	
	
private:
	int size;
	int x_;
	int y_;
	int matrix[4][4] = { {0} };
};
