#include "const.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* mainWindow;
extern SDL_Renderer* mainRenderer;

enum BlockType
{
	BLOCK_Z=1,
	BLOCK_S,
	BLOCK_J,
	BLOCK_L,
	BLOCK_O,
	BLOCK_I,
	BLOCK_T,
	BLOCK_DEFAULT,
	BLOCK_TOTAL
};

//enum soundEffect
//{
//	gameOverSound,
//	moveSound,
//	countSound,
//	rotateSound
//};

bool initSDL();

void loadTexture();

void close();

bool loadStat();

bool loadBlock();

class Texture
{
public:
	Texture();

	~Texture();

	bool loadFromFile(string path);

	bool loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font *font);

	void free();

	void render(int x, int y, SDL_Rect* clip = NULL, int size=0);
	int mWidth;
	int mHeight;

private:
	SDL_Texture* mTexture;
	


};

extern SDL_Rect BlockRect[BLOCK_TOTAL];
extern Texture BlockSheet;
extern Texture ShadeSheet;
extern Texture MainScreen;
extern Texture HelpScreen[3];
extern Texture GameOver;

extern Texture GameOver2;
extern Texture Winner;
extern Texture Loser;

extern Texture onePlayerModeScreen;
extern Texture twoPlayerModeScreen;
extern Texture pauseBackground;
extern Texture countDown[3];
extern Texture Mute;
extern Texture Unmute;

extern TTF_Font* gFont;
extern SDL_Color scoreColor;
extern SDL_Color levelColor;
extern SDL_Color lineColor;
extern SDL_Color loseColor;


#pragma once
