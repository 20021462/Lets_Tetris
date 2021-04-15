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
		MainScreen.loadFromFile("texture/mainScreen.png");
		onePlayerModeScreen.loadFromFile("texture/1playerPlayingScreen.png");
		twoPlayerModeScreen.loadFromFile("texture/2playerPlayingScreen.png");
		pauseBackground.loadFromFile("texture/pauseBackground.png");
		loadBlock();
		loadButton();
		loadStat();

		bool quit = false;
		SDL_Event e;

		while (!quit)
		{
			SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(mainRenderer);

			bool quitMode = false;
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
				onePlayerMode.lose = false;


				while (!onePlayerMode.lose && !quitMode && !quit)
				{
					for (int i = 0; i < 5; i++)
					{
						block[i].generate(nextBlock[i]);
					}
					bool canHold = true;
					while (!block[1].collide(onePlayerMode.fieldMatrix) && !quitMode && !quit)
					{
						if (SDL_GetTicks() > totalTime)
						{
							totalTime += onePlayerMode.Time;
							block[1].move(0, 1);
						}

						onePlayerModeScreen.render(0, 0, NULL);
						block[0].printNext(579, 283, 35);
						block[2].printNext(1275, 283, 35);
						block[3].printNext(1280, 547, 30);
						block[4].printNext(1284, 781, 25);
						onePlayerMode.getStat(0);
						onePlayerMode.printField(760);

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
								block[0].printNext(574, 303 - 20, 35);
								block[1].print(755);
								break;

							case SDLK_ESCAPE: case SDLK_p:
								userChoice = PAUSE_RESUME;
								while (pauseModeChosen == PAUSE_TOTAL)
								{
									onePlayerModeScreen.render(0, 0, NULL);
									onePlayerMode.getStat(0);
									pauseBackground.render(0, 0, NULL);
									printPauseButton();
									SDL_RenderPresent(mainRenderer);
									SDL_PollEvent(&e);
									if (e.type == SDL_KEYDOWN)
									{
										switch (e.key.keysym.sym)
										{
										case SDLK_RIGHT: case SDLK_d:
											if (userChoice == PAUSE_TOTAL - 1) userChoice = 0;
											else userChoice++;
											break;
										case SDLK_LEFT: case SDLK_a:
											if (userChoice == 0) userChoice = PAUSE_TOTAL - 1;
											else userChoice--;
											break;
										case SDLK_SPACE: case SDLK_RETURN:
											pauseModeChosen = userChoice;
											break;
										default:
											break;
										}
									}
									e.type = NULL;
								}
								switch (pauseModeChosen)
								{
								case PAUSE_RESUME:
									totalTime = SDL_GetTicks();
									totalTime += onePlayerMode.Time;
									break;
								case PAUSE_NEW_GAME:
									totalTime = 0;
									onePlayerMode.reset();
									quitMode = true;
									gameModeChosen = CHOOSE_ONE_PLAYER_MODE;
									break;
								case PAUSE_HOME:
									totalTime = 0;
									onePlayerMode.reset();
									quitMode = true;
									gameModeChosen = CHOOSE_TOTAL;
									break;
								}
								pauseModeChosen = PAUSE_TOTAL;
								userChoice = 0;
								break;


							default:
								break;
							}
						}
						e.type = NULL;
						if (quitMode) {
							freeList(nextBlock, 5);
							break;
						}

						onePlayerMode.shade(block[1], 760);
						if (!block[1].collide(onePlayerMode.fieldMatrix)) block[1].print(760);
						SDL_RenderPresent(mainRenderer);
					}
					if (quitMode) break;

					onePlayerMode.unite(block[1]);
					newBlockGenerate(nextBlock, 5);

					onePlayerMode.lineClear();
					if (onePlayerMode.checkLose())
					{
						onePlayerMode.reset();
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
				playerOneField.lose = false;
				playerTwoField.lose = false;

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

				while ((!playerOneField.lose || !playerTwoField.lose) && !quitMode && !quit)
				{
					while (!p1Block[1].collide(playerOneField.fieldMatrix) && !p2Block[1].collide(playerTwoField.fieldMatrix) && !quitMode && !quit)
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
						twoPlayerModeScreen.render(0, 0, NULL);

						p1Block[0].printNext(99, 283, 35);
						p1Block[2].printNext(795, 283, 35);
						p1Block[3].printNext(800, 547, 30);
						p1Block[4].printNext(805, 781, 25);
						p2Block[0].printNext(1059, 283, 35);
						p2Block[2].printNext(1755, 283, 35);
						p2Block[3].printNext(1760, 547, 30);
						p2Block[4].printNext(1765, 781, 25);

						playerOneField.getStat(-475);
						playerTwoField.getStat(485);
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
								p1Block[0].printNext(99, 303 - 20, 35);
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
								p2Block[0].printNext(1059, 303 - 20, 35);
								p2Block[1].print(1240);
								break;

							case SDLK_ESCAPE: case SDLK_p:
								userChoice = PAUSE_RESUME;
								while (pauseModeChosen == PAUSE_TOTAL)
								{
									twoPlayerModeScreen.render(0, 0, NULL);
									playerOneField.getStat(-475);
									playerTwoField.getStat(485);
									pauseBackground.render(0, 0, NULL);
									printPauseButton();
									SDL_RenderPresent(mainRenderer);
									SDL_PollEvent(&e);
									if (e.type == SDL_KEYDOWN)
									{
										switch (e.key.keysym.sym)
										{
										case SDLK_RIGHT: case SDLK_d:
											if (userChoice == PAUSE_TOTAL - 1) userChoice = 0;
											else userChoice++;
											break;
										case SDLK_LEFT: case SDLK_a:
											if (userChoice == 0) userChoice = PAUSE_TOTAL - 1;
											else userChoice--;
											break;
										case SDLK_SPACE: case SDLK_RETURN:
											pauseModeChosen = userChoice;
											break;
										default:
											break;
										}
									}
									e.type = NULL;
								}
								switch (pauseModeChosen)
								{
								case PAUSE_RESUME:
									p1TotalTime = SDL_GetTicks();
									p1TotalTime += playerOneField.Time;
									p2TotalTime = SDL_GetTicks();
									p2TotalTime += playerTwoField.Time;
									break;
								case PAUSE_NEW_GAME:
									p1TotalTime = 0;
									p2TotalTime = 0;
									playerOneField.reset();
									playerTwoField.reset();
									quitMode = true;
									gameModeChosen = CHOOSE_TWO_PLAYER_MODE;
									break;
								case PAUSE_HOME:
									p1TotalTime = 0;
									p2TotalTime = 0;
									playerOneField.reset();
									playerTwoField.reset();
									quitMode = true;
									gameModeChosen = CHOOSE_TOTAL;
									break;
								}
								pauseModeChosen = PAUSE_TOTAL;
								userChoice = 0;
								break;

							default:
								break;
							}
						}
						e.type = NULL;
						if (quitMode) {
							freeList(p1NextBlock, 5);
							freeList(p2NextBlock, 5);
							freeList(fullList, 50);
							break;
						}
						playerOneField.shade(p1Block[1], 280);
						playerTwoField.shade(p2Block[1], 1240);
						if (!p1Block[1].collide(playerOneField.fieldMatrix)) p1Block[1].print(280);
						if (!p2Block[1].collide(playerTwoField.fieldMatrix)) p2Block[1].print(1240);

						SDL_RenderPresent(mainRenderer);

					}
					if (quitMode) break;

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

					if (playerOneField.checkLose() || playerTwoField.checkLose())
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
				quit = true;
				break;
			}
			
		}
	}

	close();
	return 0;
}
