#pragma once
#include "render.h"
#include "const.h"
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
<<<<<<< Updated upstream
	
	
private:
=======

	bool collide();

	void move(int x, int y);
	void rotate(int matrix[4][4]=NULL);
	void gravity();
	void moveRight();
	void moveLeft();
	void hardDrop();
	void control(SDL_Event keypress);

	void print();

	int matrix[4][4] = { {0} };
	int size;
>>>>>>> Stashed changes
	int x_;
	int y_;
	int matrix[4][4] = { {0} };
};
