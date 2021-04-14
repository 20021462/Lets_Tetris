#include "render.h"
#include "const.h"
#include "block.h"
#include "playerField.h"
#include "button.h"

int main(int argc, char* args[])
{
	srand(time(0));
	if (!initSDL())
	{
		cout << "Failed to initialize!\n";
	}
	else
	{
		MainScreen.loadFromFile("texture/mainScreen2.png");
		Board.loadFromFile("texture/playing_screen.png");
		loadBlock();
		loadButton();
		loadStat();

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
						generateBlockId(nextBlock, 5);
						MainScreen.render(0, 0, NULL);

						while (!onePlayerMode.lose() && !quit)
						{
							for (int i = 0; i < 5; i++)
							{
								block[i].generate(nextBlock[i]);
							}
							bool canHold = true;
							while (!block[1].collide(onePlayerMode.fieldMatrix))
							{
								if (SDL_GetTicks() > totalTime)
								{
									totalTime += onePlayerMode.Time;
									block[1].move(0, 1);
								}

								Board.render(475, 0, NULL);
								block[0].printNext(574, 303, 35);
								block[2].printNext(1270, 303, 35);
								block[3].printNext(1275, 567, 30);
								block[4].printNext(1279, 801, 25);
								onePlayerMode.getStat();
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
										block[1].rotate(block[1].matrix, onePlayerMode.fieldMatrix);
										break;

									case SDLK_DOWN: case SDLK_s:
										block[1].move(0, 1);
										onePlayerMode.Score++;
										break;

									case SDLK_RIGHT: case SDLK_d:
										block[1].moveRight(onePlayerMode.fieldMatrix);
										break;

									case SDLK_LEFT: case SDLK_a:
										block[1].moveLeft(onePlayerMode.fieldMatrix);
										break;

									case SDLK_SPACE: case SDLK_KP_ENTER: case SDLK_RETURN:
										block[1].hardDrop(onePlayerMode.fieldMatrix, onePlayerMode.Score);
										break;

									case SDLK_c:
										if (!canHold) break;
										canHold = false;
										hold(block, nextBlock, 5);
										block[0].printNext(574, 303, 35);
										block[1].print(755);
										break;

									default:
										break;
									}
								}
								e.type = NULL;

								onePlayerMode.shade(block[1], 755);
								if (!block[1].collide(onePlayerMode.fieldMatrix)) block[1].print(755);
								SDL_RenderPresent(mainRenderer);
							}

							onePlayerMode.unite(block[1]);
							newBlockGenerate(nextBlock, 5);

							onePlayerMode.lineClear();
							if (onePlayerMode.lose())
							{
								totalTime = 0;
								gameModeChosen = CHOOSE_TOTAL;
								break;
							}
						}
						break;

					case CHOOSE_TWO_PLAYER_MODE:
						p1TotalTime += playerOneField.Time;
						p1TotalTime += SDL_GetTicks();
						p2TotalTime += playerTwoField.Time;
						p2TotalTime += SDL_GetTicks();
						p1Place = 1;
						p2Place = 1;

						generateBlockId(fullList, 50);

						tmpLine1 = 0;
						tmpLine2 = 0;

						for (int i = 0; i < 5; i++)
						{
							p1Block[i].generate(fullList[i]);
							p2Block[i].generate(fullList[i]);
						}
						getBlockId(p1NextBlock, fullList, p1Place);
						getBlockId(p2NextBlock, fullList, p2Place);

						MainScreen.render(0, 0, NULL);

						while ((!playerOneField.lose() || !playerTwoField.lose()) && !quit )
						{
							while (!p1Block[1].collide(playerOneField.fieldMatrix) && !p2Block[1].collide(playerTwoField.fieldMatrix))
							{
								if (SDL_GetTicks() > p1TotalTime)
								{
									p1TotalTime += playerOneField.Time;
									p1Block[1].move(0, 1);
								}
								if (SDL_GetTicks() > p2TotalTime)
								{
									p2TotalTime += playerTwoField.Time;
									p2Block[1].move(0, 1);
								}
								Board.render(0, 0, NULL);
								Board.render(960, 0, NULL);

								p1Block[0].printNext(99, 303, 35);
								p1Block[2].printNext(795, 303, 35);
								p1Block[3].printNext(800, 567, 30);
								p1Block[4].printNext(805, 801, 25);

								p2Block[0].printNext(1059, 303, 35);
								p2Block[2].printNext(1755, 303, 35);
								p2Block[3].printNext(1760, 567, 30);
								p2Block[4].printNext(1765, 801, 25);

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
									case SDLK_w:
										p1Block[1].rotate(p1Block[1].matrix, playerOneField.fieldMatrix);
										break;

									case SDLK_s:
										p1Block[1].move(0, 1);
										playerOneField.Score++;
										break;

									case SDLK_d:
										p1Block[1].moveRight(playerOneField.fieldMatrix);
										break;

									case SDLK_a:
										p1Block[1].moveLeft(playerOneField.fieldMatrix);
										break;

									case SDLK_SPACE:
										p1Block[1].hardDrop(playerOneField.fieldMatrix, playerOneField.Score);
										break;

									case SDLK_c:
										if (!p1CanHold) break;
										p1CanHold = false;
										hold(p1Block, p1NextBlock, 5);
										p1Block[0].printNext(99, 303, 35);
										p1Block[1].print(280);
										break;

									case SDLK_UP:
										p2Block[1].rotate(p2Block[1].matrix, playerTwoField.fieldMatrix);
										break;

									case SDLK_DOWN:
										p2Block[1].move(0, 1);
										playerTwoField.Score++;
										break;

									case SDLK_RIGHT:
										p2Block[1].moveRight(playerTwoField.fieldMatrix);
										break;

									case SDLK_LEFT:
										p2Block[1].moveLeft(playerTwoField.fieldMatrix);
										break;

									case SDLK_KP_ENTER: case SDLK_RETURN:
										p2Block[1].hardDrop(playerTwoField.fieldMatrix, playerTwoField.Score);
										break;

									case SDLK_RCTRL:
										if (!p2CanHold) break;
										p2CanHold = false;
										hold(p2Block, p2NextBlock, 5);
										p2Block[0].printNext(1059, 303, 35);
										p2Block[1].print(1240);
										break;

									default:
										break;
									}
								}
								e.type = NULL;

								playerOneField.shade(p1Block[1], 280);
								playerTwoField.shade(p2Block[1], 1240);
								if (!p1Block[1].collide(playerOneField.fieldMatrix)) p1Block[1].print(280);
								if (!p2Block[1].collide(playerTwoField.fieldMatrix)) p2Block[1].print(1240);

								SDL_RenderPresent(mainRenderer);

							}

							if (p1Block[1].collide(playerOneField.fieldMatrix))
							{
								playerOneField.unite(p1Block[1]);
								p1Place++;
								getBlockId(p1NextBlock, fullList, p1Place);
								for (int i = 1; i < 5; i++)
								{
									p1Block[i].generate(p1NextBlock[i]);
								}
								p1CanHold = true;
							}
							if (p2Block[1].collide(playerTwoField.fieldMatrix))
							{
								playerTwoField.unite(p2Block[1]);
								p2Place++;
								getBlockId(p2NextBlock, fullList, p2Place);
								for (int i = 1; i < 5; i++)
								{
									p2Block[i].generate(p2NextBlock[i]);
								}
								p2CanHold = true;
							}
							while (p1Place > 1 && p2Place > 1)
							{
								newBlockGenerate(fullList, 50);
								p1Place--;
								p2Place--;
							}

							if (playerOneField.lineClear() || playerTwoField.lineClear())
							{
								if (playerOneField.lineClear())
								{
									//playerTwoField.sendBlock(2);
									//tmpLine1 = playerOneField.Line;
								}
								if (playerTwoField.lineClear())
								{
									//playerOneField.sendBlock(2);
									//tmpLine2 = playerTwoField.Line;
								}
							}

							if (playerOneField.lose() || playerTwoField.lose())
							{
								playerOneField.reset();
								playerTwoField.reset();
								p1TotalTime = 0;
								p2TotalTime = 0;
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
