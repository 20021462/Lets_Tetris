#pragma once
#include "render.h"
#include "Const.h"
class Block
{
public:
	enum Block_type
	{
		Z=0,
		S,
		J,
		L,
		O,
		I,
		T,
	};
	Block(Block_type type);
	~Block();
	void move(int x, int y);
	void rotate(int matrix[4][4]);
	int x();
	int y();
	
	
private:
	int x_;
	int y_;
	int matrix[4][4] = { {0} };
};
