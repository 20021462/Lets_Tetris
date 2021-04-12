#include "render.h"
#include "const.h"
#include "block.h"
#include "playerField.h"
#include "button.h"

int main(int argc, char* args[])
{
	srand(time(0));

	unsigned long long int totalTime = 0;
	unsigned long long int totalTime1 = 0;
	unsigned long long int totalTime2 = 0;

	int tmpLine1 = 0;
	int tmpLine2 = 0;

	Block block;
	Block block1;
	Block block2;


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
							case SDLK_UP: case SDLK_w:
								if (userChoice == 0) userChoice = CHOOSE_TOTAL - 1;
								else userChoice--;
								break;

							case SDLK_DOWN: case SDLK_s:
								if (userChoice == CHOOSE_TOTAL - 1) userChoice = 0;
								else userChoice++;
								break;

							case SDLK_SPACE: case SDLK_KP_ENTER: case SDLK_RETURN:
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
								onePlayerMode.printField(755);
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
									case SDLK_UP: case SDLK_w:
										block.rotate(block.matrix, onePlayerMode.fieldMatrix);
										break;

									case SDLK_DOWN: case SDLK_s:
										block.move(0, 1);
										break;

									case SDLK_RIGHT: case SDLK_d:
										block.moveRight(onePlayerMode.fieldMatrix);
										break;

									case SDLK_LEFT: case SDLK_a:
										block.moveLeft(onePlayerMode.fieldMatrix);
										break;

									case SDLK_SPACE: case SDLK_KP_ENTER: case SDLK_RETURN:
										block.hardDrop(onePlayerMode.fieldMatrix);
										break;

									default:
										break;
									}
								}
								//block.control(e);
								e.type = NULL;

								onePlayerMode.shade(block, 755);
								block.print(755,30);
								SDL_RenderPresent(mainRenderer);
								if (onePlayerMode.lineClear()) {
									MainScreen.render(0, 0, NULL);
									Board.render(750, 135, NULL);
									onePlayerMode.printField(755);
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

					case CHOOSE_TWO_PLAYER_MODE:
						totalTime1 += playerOneField.Time;
						totalTime1 += SDL_GetTicks();

						totalTime2 += playerTwoField.Time;
						totalTime2 += SDL_GetTicks();

						block1.generate(rand() % 7 + 1);
						block2.generate(rand() % 7 + 1);

						tmpLine1 = 0;
						tmpLine2 = 0;

						while ((!playerOneField.lose() || !playerTwoField.lose()) && !quit )
						{
							while (!block1.collide(playerOneField.fieldMatrix) && !block2.collide(playerTwoField.fieldMatrix))
							{
								if (SDL_GetTicks() > totalTime1)
								{
									totalTime1 += playerOneField.Time;
									block1.move(0, 1);
								}
								if (SDL_GetTicks() > totalTime2)
								{
									totalTime2 += playerTwoField.Time;
									block2.move(0, 1);
								}
								MainScreen.render(0, 0, NULL);
								Board.render(275, 135, NULL);
								Board.render(1235, 135, NULL);
								playerOneField.printField(280);
								playerTwoField.printField(1240);

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
										block1.rotate(block1.matrix, playerOneField.fieldMatrix);
										break;

									case SDLK_DOWN:
										block1.move(0, 1);
										break;

									case SDLK_RIGHT:
										block1.moveRight(playerOneField.fieldMatrix);
										break;

									case SDLK_LEFT:
										block1.moveLeft(playerOneField.fieldMatrix);
										break;

									case SDLK_KP_ENTER: case SDLK_RETURN:
										block1.hardDrop(playerOneField.fieldMatrix);
										break;

									case SDLK_w:
										block2.rotate(block2.matrix, playerTwoField.fieldMatrix);
										break;

									case SDLK_s:
										block2.move(0, 1);
										break;

									case SDLK_d:
										block2.moveRight(playerTwoField.fieldMatrix);
										break;

									case SDLK_a:
										block2.moveLeft(playerTwoField.fieldMatrix);
										break;

									case SDLK_SPACE:
										block2.hardDrop(playerTwoField.fieldMatrix);
										break;

									default:
										break;
									}
								}
								e.type = NULL;

								playerOneField.shade(block1, 280);
								playerTwoField.shade(block2, 1240);
								block1.print(280);
								block2.print(1240);

								SDL_RenderPresent(mainRenderer);

							}

							if (block1.collide(playerOneField.fieldMatrix))
							{
								playerOneField.unite(block1);
								block1.generate(rand() % 7 + 1);
							}
							if (block2.collide(playerTwoField.fieldMatrix))
							{
								playerTwoField.unite(block2);
								block2.generate(rand() % 7 + 1);
							}

							if (playerOneField.lineClear() || playerTwoField.lineClear())
							{
								MainScreen.render(0, 0, NULL);
								Board.render(275, 135, NULL);
								Board.render(1235, 135, NULL);
								if (playerOneField.lineClear())
								{
									playerTwoField.sendBlock(2);
									//tmpLine1 = playerOneField.Line;
								}
								if (playerTwoField.lineClear())
								{
									playerOneField.sendBlock(2);
									//tmpLine2 = playerTwoField.Line;
								}
								playerOneField.printField(280);
								playerTwoField.printField(1240);
								SDL_RenderPresent(mainRenderer);
							}

							if (playerOneField.lose() || playerTwoField.lose())
							{
								totalTime1 = 0;
								totalTime2 = 0;
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
