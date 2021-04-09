#include "button.h"

int userChoice = 0;

const int BUTTON_WIDTH = 350;
const int BUTTON_HEIGHT = 97;

SDL_Rect ButtonTexture[STATE_TOTAL];
Button buttonChoice[CHOOSE_TOTAL];

Button::Button()
{
	buttonChoice = 0;
	x = 0;
	y = 0;
}

Button::~Button()
{

}

void Button::render()
{
	if (buttonChoice != userChoice) buttonTexture.render(x, y, ButtonTexture[NORMAL]);
	else buttonTexture.render(x, y, ButtonTexture[CHOSEN]);
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
	ButtonTexture[CHOSEN].x = BUTTON_HEIGHT;

	buttonChoice[CHOOSE_ONE_PLAYER_MODE].buttonTexture.loadFromFile("texture/option_box_1");
	buttonChoice[CHOOSE_TWO_PLAYER_MODE].buttonTexture.loadFromFile("texture/option_box_2");
	buttonChoice[CHOOSE_HELP].buttonTexture.loadFromFile("texture/option_box_3");
	buttonChoice[CHOOSE_QUIT].buttonTexture.loadFromFile("texture/option_box_4");

}



