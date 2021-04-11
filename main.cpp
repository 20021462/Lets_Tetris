#include "render.h"
#include "const.h"
#include "block.h"
#include "playerField.h"
#include "button.h"

int main(int argc, char* args[])
{
	srand(time(0));
	unsigned long long int totalTime = 0;
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

			while (gameModeChosen != -1 )
			{
				switch (gameModeChosen)
				{
					case CHOOSE_TOTAL:
						MainScreen.render(0, 0, NULL);
						printButton();
						SDL_RenderPresent(mainRenderer);
						SDL_PollEvent(&e);
						if (e.type == SDL_QUIT)
						{
							gameModeChosen = -1;
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

					case CHOOSE_ONE_PLAYER_MODE:
						totalTime += onePlayerMode.Time;
						totalTime += SDL_GetTicks();
						while (gameModeChosen == CHOOSE_ONE_PLAYER_MODE)
						{
							block.generate(rand() % 7 + 1);
							while (!block.collide(onePlayerMode.fieldMatrix))
							{
								if (SDL_GetTicks() > totalTime)
								{
									totalTime += onePlayerMode.Time;
									block.move(0, 1);
								}
								MainScreen.render(0, 0, NULL);
								Board.render(750, 135, NULL);
								onePlayerMode.printField();
								SDL_PollEvent(&e);
								if (e.type == SDL_QUIT)
								{
									quit = true;
									gameModeChosen = -1;
									break;
								}
								if (e.type == SDL_KEYDOWN)
								{
									switch (e.key.keysym.sym)
									{
									case SDLK_UP:
										block.rotate(block.matrix, onePlayerMode.fieldMatrix);
										break;

									case SDLK_DOWN:
										block.move(0, 1);
										break;

									case SDLK_RIGHT:
										block.moveRight(onePlayerMode.fieldMatrix);
										break;

									case SDLK_LEFT:
										block.moveLeft(onePlayerMode.fieldMatrix);
										break;

									case SDLK_SPACE:
										block.hardDrop(onePlayerMode.fieldMatrix);
										break;

									default:
										break;
									}
								}
								//block.control(e);
								e.type = NULL;

								onePlayerMode.shade(block);
								block.print();
								SDL_RenderPresent(mainRenderer);
								if (onePlayerMode.lineClear()) {
									MainScreen.render(0, 0, NULL);
									Board.render(750, 135, NULL);
									block.print();
									SDL_RenderPresent(mainRenderer);
								}

							}
							onePlayerMode.unite(block);
							if (onePlayerMode.lose())
							{
								totalTime = 0;
								gameModeChosen = CHOOSE_TOTAL;
								break;
							}
						}
						break;

					case CHOOSE_QUIT:
						gameModeChosen = -1;
						quit = true;
						break;
				}
			}
		}
	}

	close();
	return 0;
}
