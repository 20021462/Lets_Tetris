#include "const.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* mainWindow;
extern SDL_Renderer* mainRenderer;

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

extern SDL_Rect BlockRect[BLOCK_TOTAL];
extern Texture BlockSheet;
extern Texture ShadeSheet;
extern Texture Board;
extern Texture MainScreen;



#pragma once
