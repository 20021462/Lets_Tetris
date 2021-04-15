#pragma once
#include "const.h"
#include "block.h"

//extern int Level;
//extern int Line;
//extern int Point;
//extern double Time;

class Field
{
public :
	int fieldMatrix[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
	int Level = 1;
	int Line = 0;
	int Score = 0;
	int Time = 1000;

	void printField(int x);
	void unite(Block& block);
	void fieldDown(int line);
	bool lineClear();
	void shade(Block& block, int x);
	bool lose();
	void reset();

	void getStat(int x);
	//void sendBlock(int line);

	Texture scoreTexture;
	Texture lineTexture;
	Texture levelTexture;

private :

};

extern Field onePlayerMode;
extern Field playerOneField;
extern Field playerTwoField;