#pragma once
#include "const.h"
#include "Block.h"

extern int helpChoice;
extern int userChoice;
extern int gameModeChosen;
extern int pauseModeChosen;

enum HelpChoices
{
	HELP_1,
	HELP_2,
	HELP_3,
	HELP_TOTAL,
};

enum ButtonChoice
{
	CHOOSE_ONE_PLAYER_MODE,
	CHOOSE_TWO_PLAYER_MODE,
	CHOOSE_HELP,
	CHOOSE_QUIT,
	CHOOSE_TOTAL,
};

enum PauseButton
{
	PAUSE_NEW_GAME,
	PAUSE_RESUME,
	PAUSE_HOME,
	PAUSE_TOTAL,
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

	void render(SDL_Rect rect[]);

private:

};

void loadButton();
void printButton();
void printPauseButton();

extern SDL_Rect ButtonTexture[STATE_TOTAL];
extern Button buttonChoice[CHOOSE_TOTAL];
extern SDL_Rect PauseButtonTexture[STATE_TOTAL];
extern Button pauseButton[PAUSE_TOTAL];

