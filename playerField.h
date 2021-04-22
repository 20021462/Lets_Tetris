#pragma once
#include "const.h"
#include "block.h"
#include "sound.h"

class Field
{
public :
	int fieldMatrix[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
	int Level = 1;
	int Line = 0;
	int Score = 0;
	int Time = 1000;
	bool lose = false;

	void printField(int x);
	void unite(Block& block);
	void fieldDown(int line);
	bool lineClear();
	void shade(Block& block, int x);
	bool checkLose();
	void reset();

	void getStat(int x);
	void printScore(int x, int y, int size, SDL_Color color);
	//void sendBlock(int line);

	Texture scoreTexture;
	Texture lineTexture;
	Texture levelTexture;

private :

};

extern Field onePlayerMode;
extern Field playerOneField;
extern Field playerTwoField;