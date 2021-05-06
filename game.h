#pragma once
#include "render.h"
#include "const.h"
#include "block.h"
#include "playerField.h"
#include "button.h"
#include "sound.h"
#include "score.h"

class game
{
public:
	game();
	~game();

	bool quitMode = false;
	bool quit = false;
	SDL_Event e;

	void play();
	
private:

};


