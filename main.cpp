#include "render.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 900;
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 24;

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

int player1Board[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

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

SDL_Rect BlockRect[BLOCK_TOTAL];
Texture BlockSheet;
Texture Board;

bool initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL couldn't initialize ! Error : " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		mainWindow = SDL_CreateWindow("Let's Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mainWindow == NULL) {
			cout << "Window couldn't be created ! Error : " << SDL_GetError() << endl;
			return false;
		}
		else {
			mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
			if (mainRenderer == NULL) {
				cout << "Renderer couldn't be created ! Error : " << SDL_GetError() << endl;
				return false;
			}
			else {
				SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
					return false;
				}
			}
		}
	}
	return true;
}

void close()
{
	BlockSheet.free();

	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;
	mainRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool loadBlock()
{
	if (!BlockSheet.loadFromFile("texture/Block.png",mainRenderer))
	{
		cout << "Failed to load block sheet" << endl;
		return false;
	}
	else
	{
		BlockRect[BLOCK_Z].x = 0;
		BlockRect[BLOCK_Z].y = 0;
		BlockRect[BLOCK_Z].w = 40;
		BlockRect[BLOCK_Z].h = 40;

		BlockRect[BLOCK_S].x = 40;
		BlockRect[BLOCK_S].y = 0;
		BlockRect[BLOCK_S].w = 40;
		BlockRect[BLOCK_S].h = 40;

		BlockRect[BLOCK_J].x = 80;
		BlockRect[BLOCK_J].y = 0;
		BlockRect[BLOCK_J].w = 40;
		BlockRect[BLOCK_J].h = 40;

		BlockRect[BLOCK_L].x = 120;
		BlockRect[BLOCK_L].y = 0;
		BlockRect[BLOCK_L].w = 40;
		BlockRect[BLOCK_L].h = 40;

		BlockRect[BLOCK_O].x = 0;
		BlockRect[BLOCK_O].y = 40;
		BlockRect[BLOCK_O].w = 40;
		BlockRect[BLOCK_O].h = 40;

		BlockRect[BLOCK_I].x = 40;
		BlockRect[BLOCK_I].y = 40;
		BlockRect[BLOCK_I].w = 40;
		BlockRect[BLOCK_I].h = 40;

		BlockRect[BLOCK_T].x = 80;
		BlockRect[BLOCK_T].y = 40;
		BlockRect[BLOCK_T].w = 40;
		BlockRect[BLOCK_T].h = 40;

		BlockRect[BLOCK_DEFAULT].x = 120;
		BlockRect[BLOCK_DEFAULT].y = 40;
		BlockRect[BLOCK_DEFAULT].w = 40;
		BlockRect[BLOCK_DEFAULT].h = 40;
	}
	return true;
}

void print()
{
	for (int i = 4; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			if (player1Board[i][j] == 0) continue;
			if (player1Board[i][j] > BLOCK_TOTAL) BlockSheet.render(150 + 40 * j, 50 + 40 * (i - 4), &BlockRect[player1Board[i][j] - BLOCK_TOTAL],mainRenderer);
			else BlockSheet.render(150 + 40 * j, 50 + 40 * (i - 4), &BlockRect[player1Board[i][j]],mainRenderer);
		}
	}
}

void generateBlock(int BlockType)
{
	switch (BlockType)
	{
		case BLOCK_Z : 
			player1Board[0][5] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[1][5] = BlockType;
			player1Board[2][4] = BlockType;
			break;

		case BLOCK_S:
			player1Board[0][4] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[1][5] = BlockType;
			player1Board[2][5] = BlockType;
			break;

		case BLOCK_J:
			player1Board[0][5] = BlockType;
			player1Board[1][5] = BlockType;
			player1Board[2][5] = BlockType;
			player1Board[2][4] = BlockType;
			break;

		case BLOCK_L:
			player1Board[0][4] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[2][4] = BlockType;
			player1Board[2][5] = BlockType;
			break;

		case BLOCK_I:
			player1Board[0][4] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[2][4] = BlockType;
			player1Board[3][4] = BlockType;
			break;

		case BLOCK_O:
			player1Board[0][4] = BlockType;
			player1Board[0][5] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[1][5] = BlockType;
			break;

		case BLOCK_T:
			player1Board[0][4] = BlockType;
			player1Board[1][3] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[1][5] = BlockType;
			break;
	}
}

void gravity()
{

}

int main(int argc, char* args[])
{

	srand(time(NULL));
	int tmp = rand() % 7 + 1;
	generateBlock(tmp);

	if (!initSDL())
	{
		cout << "Failed to initialize!\n";
	}
	else
	{
		if (!Board.loadFromFile("texture/Board.png",mainRenderer))
		{
			cout << "Failed to load board" << endl;
		}
		else
		{
			if (!loadBlock())
			{
				cout << "Failed to load block sheet" << endl;
			}
			else
			{
				bool quit = false;
				SDL_Event e;

				while (!quit)
				{
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
					}

					SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(mainRenderer);

					while (player1Board[23][4] != 1) {
						for (int i = 22; i >= 0; i--) {
							for (int j = 0; j < 10; j++) {
								player1Board[i + 1][j] = player1Board[i][j];
								if (i == 0) player1Board[i][j] = 0;
							}
						}
						Board.render(145, 45, NULL,mainRenderer);
						print();
						SDL_RenderPresent(mainRenderer);
						SDL_Delay(500);
					}
				}
			}

		}
	}

	close();
	return 0;
}
