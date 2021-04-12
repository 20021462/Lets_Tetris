#pragma once
#include "const.h"
#include "Block.h"

extern int userChoice;
extern int gameModeChosen;


enum ButtonChoice
{
	CHOOSE_ONE_PLAYER_MODE,
	CHOOSE_TWO_PLAYER_MODE,
	CHOOSE_HELP,
	CHOOSE_QUIT,
	CHOOSE_TOTAL,
};

enum ButtonState
{
	NORMAL,
	CHOSEN,
	STATE_TOTAL,
};

class Button
{
public:
	Button();
	~Button();

	int buttonId;
	int x, y;
	Texture buttonTexture;

	void render();

private:

};

void loadButton();
void printButton();
void controlButton(SDL_Event& keypress);

extern SDL_Rect ButtonTexture[STATE_TOTAL];
extern Button buttonChoice[CHOOSE_TOTAL];

