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

	Block();
	~Block();

	void move(int x, int y);
	void rotate(int matrix[4][4]=NULL);
	bool collide();
	bool is_block(int x, int y);
	void gravity();
	void print();
	void generate(int type);

	int x();
	int y();
	int matrix[4][4] = { {0} };
	
private:
	int size;
	int x_;
	int y_;

};
