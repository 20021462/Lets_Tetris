#include "button.h"

int userChoice = 0;
int gameModeChosen = CHOOSE_TOTAL;
int pauseModeChosen = PAUSE_TOTAL;

const int BUTTON_WIDTH = 500;
const int BUTTON_HEIGHT = 90;

const int PAUSE_BUTTON_SIZE = 130;

SDL_Rect ButtonTexture[STATE_TOTAL];
SDL_Rect PauseButtonTexture[STATE_TOTAL];
Button buttonChoice[CHOOSE_TOTAL];
Button pauseButton[PAUSE_TOTAL];

Button::Button()
{
	buttonId = 0;
	x = 0;
	y = 0;
}

Button::~Button()
{

}

void Button::render(SDL_Rect rect[])
{
	if (buttonId != userChoice) buttonTexture.render(x, y, &rect[NORMAL]);
	else if (&rect[1] == &PauseButtonTexture[1]) buttonTexture.render(x, y - 114, &rect[CHOSEN]);
	else buttonTexture.render(x, y, &rect[CHOSEN]);
}

void loadButton()
{
	ButtonTexture[NORMAL].x = 0;
	ButtonTexture[NORMAL].y = 0;
	ButtonTexture[NORMAL].w = BUTTON_WIDTH;
	ButtonTexture[NORMAL].h = BUTTON_HEIGHT;

	ButtonTexture[CHOSEN].x = 0;
	ButtonTexture[CHOSEN].y = BUTTON_HEIGHT;
	ButtonTexture[CHOSEN].w = BUTTON_WIDTH;
	ButtonTexture[CHOSEN].h = BUTTON_HEIGHT;

	buttonChoice[CHOOSE_ONE_PLAYER_MODE].buttonTexture.loadFromFile("texture/1player.png");
	buttonChoice[CHOOSE_TWO_PLAYER_MODE].buttonTexture.loadFromFile("texture/2player.png");
	buttonChoice[CHOOSE_HELP].buttonTexture.loadFromFile("texture/help.png");
	buttonChoice[CHOOSE_QUIT].buttonTexture.loadFromFile("texture/quit.png");

	for (int i = 0; i < CHOOSE_TOTAL; i++)
	{
		buttonChoice[i].buttonId = i;
		buttonChoice[i].x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
		buttonChoice[i].y = 550 + i * (35 + BUTTON_HEIGHT);
	}

	PauseButtonTexture[NORMAL].x = 0;
	PauseButtonTexture[NORMAL].y = PAUSE_BUTTON_SIZE;
	PauseButtonTexture[NORMAL].w = PAUSE_BUTTON_SIZE;
	PauseButtonTexture[NORMAL].h = PAUSE_BUTTON_SIZE;

	PauseButtonTexture[CHOSEN].x = PAUSE_BUTTON_SIZE;
	PauseButtonTexture[CHOSEN].y = 0;
	PauseButtonTexture[CHOSEN].w = PAUSE_BUTTON_SIZE;
	PauseButtonTexture[CHOSEN].h = PAUSE_BUTTON_SIZE * 2;

	pauseButton[PAUSE_RESUME].buttonTexture.loadFromFile("texture/playButton.png");
	pauseButton[PAUSE_NEW_GAME].buttonTexture.loadFromFile("texture/replayButton.png");
	pauseButton[PAUSE_HOME].buttonTexture.loadFromFile("texture/homeButton.png");

	for (int i = 0; i < PAUSE_TOTAL; i++)
	{
		pauseButton[i].buttonId = i;
		pauseButton[i].x = 680 + i * 215;
		pauseButton[i].y = 556;
	}

}

void printButton()
{
	for (int i = 0; i < CHOOSE_TOTAL; i++)
	{
		buttonChoice[i].render(ButtonTexture);
	}

}

void printPauseButton()
{
	for (int i = 0; i < PAUSE_TOTAL; i++)
	{
		pauseButton[i].render(PauseButtonTexture);
	}
}
