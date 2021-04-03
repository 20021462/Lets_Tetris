#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>

using namespace std;

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

enum BlockType
{
	EMPTY,
	BLOCK_Z,
	BLOCK_S,
	BLOCK_J,
	BLOCK_L,
	BLOCK_O,
	BLOCK_I,
	BLOCK_T,
	BLOCK_DEFAULT,
	BLOCK_TOTAL
};

bool initSDL();

void close();

bool loadBlock();

class Texture
{
public:
	Texture();

	~Texture();

	bool loadFromFile(string path);

	void free();

	void render(int x, int y, SDL_Rect* clip = NULL);

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;


};

SDL_Rect BlockRect[BLOCK_TOTAL];
Texture BlockSheet;
Texture Board;


const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 24;

int player1Board[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

void print();

void generateBlock(int BlockType);

#pragma once
