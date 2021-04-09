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

	void generate(int type);
	int x();
	int y();

	bool collide();

	void move(int x, int y);
	void rotate(int matrix[4][4]=NULL);
	void gravity();
	void moveRight();
	void moveLeft();
	void control(SDL_Event &keypress);
	void hardDrop();
	void print();
	

	int matrix[4][4] = { {0} };
	int size;
	int x_;
	int y_;
private:
	
};