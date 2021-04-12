#pragma once
#include "render.h"
#include "const.h"

class Block
{
public:

	Block();
	~Block();

	void generate(int type);
	int x();
	int y();

	bool collide(int(*field)[10]);

	void move(int x, int y);
	void rotate(int matrix[4][4] = NULL, int (*field)[10] = NULL);
	void moveRight(int(*field)[10]);
	void moveLeft(int(*field)[10]);
	void control(SDL_Event &keypress);
	void hardDrop(int(*field)[10]);
	void print(int x, int size=0);
	void printShade(int x);
	

	int matrix[4][4] = { {0} };
	int size;
	int x_;
	int y_;
private:
	
};