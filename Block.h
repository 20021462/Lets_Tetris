#pragma once
#include "render.h"
#include "const.h"

extern short int nextBlock[5];
extern short int p1NextBlock[5];
extern short int p2NextBlock[5];
extern short int fullList[50];

void generateBlockId(short matrix[], int n);
void newBlockGenerate(short matrix[], int n);
void getBlockId(short matrix[], short list[], int startPoint);

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
	void hardDrop(int(*field)[10], int& point);
	void print(int x);
	void printNext(int x, int y, int size);
	void printShade(int x);
	

	int matrix[4][4] = { {0} };
	int size;
	int x_;
	int y_;
private:
	
};

extern Block block[5];
extern Block p1Block[5];
extern Block p2Block[5];

void hold(Block blocks[], short matrix[], int n);