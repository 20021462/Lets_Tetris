#include "button.h"

int userChoice = 0;
int gameModeChosen = CHOOSE_TOTAL;

const int BUTTON_WIDTH = 500;
const int BUTTON_HEIGHT = 90;

SDL_Rect ButtonTexture[STATE_TOTAL];
Button buttonChoice[CHOOSE_TOTAL];

Button::Button()
{
	buttonId = 0;
	x = 0;
	y = 0;
}

Button::~Button()
{

}

void Button::render()
{
	if (buttonId != userChoice) buttonTexture.render(x, y, &ButtonTexture[NORMAL]);
	else buttonTexture.render(x, y, &ButtonTexture[CHOSEN]);
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
		buttonChoice[i].y = 550 + i * (35+BUTTON_HEIGHT);
	}
}

void printButton()
{
	for (int i = 0; i < CHOOSE_TOTAL; i++)
	{
		buttonChoice[i].render();
	}

}

void controlButton(SDL_Event& keypress)
{
	if (keypress.type == SDL_KEYDOWN && keypress.key.repeat == 0)
	{
		switch (keypress.key.keysym.sym)
		{
			case SDLK_UP:
				if (userChoice == 0) userChoice = CHOOSE_TOTAL - 1;
				else userChoice--;
				break;

			case SDLK_DOWN:
				if (userChoice == CHOOSE_TOTAL) userChoice = 0;
				else userChoice++;
				break;

			case SDLK_SPACE:
				gameModeChosen = userChoice;
				break;

			default:
				break;
		}
	}

}

