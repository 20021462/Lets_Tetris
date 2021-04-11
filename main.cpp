#include "render.h"
#include "const.h"
#include "block.h"
#include "playerField.h"
#include "button.h"

int main(int argc, char* args[])
{
	long double time_ = Time;
	srand(time(0));

	Block block;

	if (!initSDL())
	{
		cout << "Failed to initialize!\n";
	}
	else
	{
		MainScreen.loadFromFile("texture/homescreen.png");
		Board.loadFromFile("texture/pastel_pf.png");
		loadBlock();
		loadButton();

		bool quit = false;
		SDL_Event e;

		while (!quit)
		{
			SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(mainRenderer);

			switch (gameModeChosen)
			{
				case CHOOSE_TOTAL :
					MainScreen.render(0, 0, NULL);
					printButton();
					SDL_RenderPresent(mainRenderer);
					SDL_PollEvent(&e);
					if (e.type == SDL_QUIT)
					{
						quit = true;
						break;
					}
					if (e.type == SDL_KEYDOWN)
					{
						//controlButton(e);
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							if (userChoice == 0) userChoice = CHOOSE_TOTAL - 1;
							else userChoice--;
							break;

						case SDLK_DOWN:
							if (userChoice == CHOOSE_TOTAL - 1) userChoice = 0;
							else userChoice++;
							break;

						case SDLK_SPACE:
							gameModeChosen = userChoice;
							break;

						default:
							break;
						}
						e.type = NULL;
					}
					break;

				case CHOOSE_ONE_PLAYER_MODE : 
					time_ += SDL_GetTicks();
					block.generate(rand() % 7 + 1);
					while (!block.collide())
					{
						if (SDL_GetTicks() > time_)
						{
							time_ += Time;
							block.move(0, 1);
						}
						MainScreen.render(0, 0, NULL);
						Board.render(750, 135, NULL);
						printField();
						SDL_PollEvent(&e);
						if (e.type == SDL_QUIT)
						{
							quit = true;
							break;
						}
						if (e.type == SDL_KEYDOWN)
						{
							switch (e.key.keysym.sym)
							{
							case SDLK_UP:
								block.rotate(block.matrix);
								break;

							case SDLK_DOWN:
								block.move(0, 1);
								break;

							case SDLK_RIGHT:
								block.moveRight();
								break;

							case SDLK_LEFT:
								block.moveLeft();
								break;

							case SDLK_SPACE:
								block.hardDrop();
								break;

							default:
								break;
							}
						}
						//block.control(e);
						e.type = NULL;

						shade(block);
						//if(!block.collide())
						block.print();
						SDL_RenderPresent(mainRenderer);
						if (lineClear()) {
							MainScreen.render(0, 0, NULL);
							Board.render(750, 135, NULL);
							block.print();
							SDL_RenderPresent(mainRenderer);
						}

					}
					unite(block);

				case CHOOSE_QUIT : 
					quit = true;
					break;
			}
			

		}
	}

	close();
	return 0;
}
