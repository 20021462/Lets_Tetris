#include "render.h"
#include "const.h"
#include "block.h"
#include "playerField.h"
#include "button.h"
#include "sound.h"

int main(int argc, char* args[])
{
	srand(time(NULL));
	if (!initSDL())
	{
		cout << "Failed to initialize!\n";
	}
	else
	{
		loadTexture();
		loadBlock();
		loadButton();
		loadStat();
		loadMedia();

		
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
				if (Mix_PlayingMusic() == 0) Mix_PlayMusic(homeScreenMusic, -1);
				if (mute) Mix_PauseMusic();

				MainScreen.render(0, 0, NULL);
				printButton();
				printMute();
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
						Mix_PlayChannel(-1, switchChoicesSound, 0);
						break;

					case SDLK_DOWN: case SDLK_s:
						if (userChoice == CHOOSE_TOTAL - 1) userChoice = 0;
						else userChoice++;
						Mix_PlayChannel(-1, switchChoicesSound, 0);
						break;

					case SDLK_SPACE: case SDLK_KP_ENTER: case SDLK_RETURN:
						gameModeChosen = userChoice;
						Mix_PlayChannel(-1, switchChoicesSound, 0);
						break;

					case SDLK_m:
						if (Mix_PausedMusic() == 1)
						{
							Mix_ResumeMusic();
							mute = false;
						}
						else
						{
							Mix_PauseMusic();
							mute = true;
						}
						break;

					default:
						break;
					}
					e.type = NULL;
				}
				break;

			case CHOOSE_ONE_PLAYER_MODE:
				Mix_HaltMusic();
				Mix_PlayMusic(ingameMusic[0], -1);
				if (mute) Mix_PauseMusic();
				totalTime += onePlayerMode.Time;
				totalTime += SDL_GetTicks();
				generateBlockId(nextBlock, 5);

				while (!onePlayerMode.checkLose() && !quitMode && !quit)
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
						printMute();

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
								Mix_PlayChannel(-1, rotateSound, 0);
								break;

							case SDLK_DOWN: case SDLK_s:
								block[1].move(0, 1);
								onePlayerMode.Score++;
								Mix_PlayChannel(-1, moveSound, 0);
								break;

							case SDLK_RIGHT: case SDLK_d:
								block[1].moveRight(onePlayerMode.fieldMatrix);
								Mix_PlayChannel(-1, moveSound, 0);
								break;

							case SDLK_LEFT: case SDLK_a:
								block[1].moveLeft(onePlayerMode.fieldMatrix);
								Mix_PlayChannel(-1, moveSound, 0);
								break;

							case SDLK_SPACE: case SDLK_KP_ENTER: case SDLK_RETURN:
								block[1].hardDrop(onePlayerMode.fieldMatrix, onePlayerMode.Score);
								break;

							case SDLK_c:
								if (!canHold) break;
								canHold = false;
								Mix_PlayChannel(-1, holdSound, 0);
								hold(block, nextBlock, 5);
								block[0].printNext(574, 303 - 20, 35);
								block[1].print(755);
								break;

							case SDLK_ESCAPE: case SDLK_p:
								Mix_PauseMusic();
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
											Mix_PlayChannel(-1, switchChoicesSound, 0);
											break;
										case SDLK_LEFT: case SDLK_a:
											if (userChoice == 0) userChoice = PAUSE_TOTAL - 1;
											else userChoice--;
											Mix_PlayChannel(-1, switchChoicesSound, 0);
											break;
										case SDLK_SPACE: case SDLK_RETURN:
											pauseModeChosen = userChoice;
											Mix_PlayChannel(-1, switchChoicesSound, 0);
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
									for (int i = 0; i < 3; i++)
									{
										onePlayerModeScreen.render(0, 0, NULL);
										countDown[i].render(0, 0, NULL);
										SDL_RenderPresent(mainRenderer);
										Mix_PlayChannel(-1, countSound, 0);
										SDL_Delay(1000);
										
									}
									Mix_PlayChannel(-1, countSound, 0);
									totalTime = SDL_GetTicks();
									totalTime += onePlayerMode.Time;
									Mix_ResumeMusic();
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
									Mix_HaltMusic();
									break;
								}
								pauseModeChosen = PAUSE_TOTAL;
								userChoice = 0;
								break;


							default:
								break;
							}
							changeMusic(e);
						}
						e.type = NULL;
						if (quitMode) {
							freeList(nextBlock, 5);
							break;
						}

						onePlayerMode.shade(block[1], 760);
						if (!block[1].collide(onePlayerMode.fieldMatrix)) block[1].print(760);
						else Mix_PlayChannel(-1, collideSound, 0);
						SDL_RenderPresent(mainRenderer);
					}
					if (quitMode) break;

					onePlayerMode.unite(block[1]);
					newBlockGenerate(nextBlock, 5);

					onePlayerMode.lineClear();
					if (onePlayerMode.checkLose())
					{	
						Mix_HaltMusic();
						Mix_PlayChannel(-1, gameOverSound, 0);
						GameOver.render(0, 0, NULL);
						onePlayerMode.printScore(1030, 665, 100, scoreColor);
						SDL_RenderPresent(mainRenderer);
						SDL_Event returnMain;
						returnMain.type = 0;
						SDL_PollEvent(&returnMain);
						while (returnMain.type != SDL_KEYDOWN) SDL_PollEvent(&returnMain);
						onePlayerMode.reset();
						totalTime = 0;
						
						gameModeChosen = CHOOSE_TOTAL;
						
						break;
					}
				}
				
				
				break;

			case CHOOSE_TWO_PLAYER_MODE:
				Mix_HaltMusic();
				Mix_PlayMusic(ingameMusic[0], -1);
				if (mute) Mix_PauseMusic();

				p1TotalTime += playerOneField.Time;
				p1TotalTime += SDL_GetTicks();
				p2TotalTime += playerTwoField.Time;
				p2TotalTime += SDL_GetTicks();
				p1Lose = false;
				p2Lose = false;
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

				while ((!playerOneField.checkLose() || !playerTwoField.checkLose()) && !quitMode && !quit)
				{
					
					while (((!p1Block[1].collide(playerOneField.fieldMatrix) && !p2Block[1].collide(playerTwoField.fieldMatrix)) 
						|| (p1Lose && !p2Block[1].collide(playerTwoField.fieldMatrix)) 
						|| (p2Lose && !p1Block[1].collide(playerOneField.fieldMatrix)))
						&& !quitMode && !quit)

					{
						if (SDL_GetTicks() > p1TotalTime && !p1Lose)
						{
							p1TotalTime += playerOneField.Time;
							p1Block[1].move(0, 1);
						}
						if (SDL_GetTicks() > p2TotalTime && !p2Lose)
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

						printMute();

						if (p1Lose)
						{
							GameOver2.render(0, 0, NULL);
							playerOneField.printScore(532, 703, 60, scoreColor);
						}
						if (p2Lose)
						{
							GameOver2.render(960, 0, NULL);
							playerTwoField.printScore(1492, 703, 60, scoreColor);
						}

						SDL_PollEvent(&e);
						if (e.type == SDL_QUIT)
						{
							quit = true;
							gameModeChosen = -1;
							break;
						}
						if (e.type == SDL_KEYDOWN)
						{
							if (!p1Lose)
							{
								switch (e.key.keysym.sym)
								{
								case SDLK_w:
									p1Block[1].rotate(p1Block[1].matrix, playerOneField.fieldMatrix);
									Mix_PlayChannel(-1, rotateSound, 0);
									break;

								case SDLK_s:
									p1Block[1].move(0, 1);
									playerOneField.Score++;
									Mix_PlayChannel(-1, moveSound, 0);
									break;

								case SDLK_d:
									p1Block[1].moveRight(playerOneField.fieldMatrix);
									Mix_PlayChannel(-1, moveSound, 0);
									break;

								case SDLK_a:
									p1Block[1].moveLeft(playerOneField.fieldMatrix);
									Mix_PlayChannel(-1, moveSound, 0);
									break;

								case SDLK_SPACE:
									p1Block[1].hardDrop(playerOneField.fieldMatrix, playerOneField.Score);

									break;

								case SDLK_c:
									if (!p1CanHold) break;
									p1CanHold = false;
									Mix_PlayChannel(-1, holdSound, 0);
									hold(p1Block, p1NextBlock, 5);
									p1Block[0].printNext(99, 303 - 20, 35);
									p1Block[1].print(280);
									break;
								}
							}
							if (!p2Lose)
							{
								switch (e.key.keysym.sym)
								{
								case SDLK_UP:
									Mix_PlayChannel(-1, rotateSound, 0);
									p2Block[1].rotate(p2Block[1].matrix, playerTwoField.fieldMatrix);
									break;

								case SDLK_DOWN:
									p2Block[1].move(0, 1);
									Mix_PlayChannel(-1, moveSound, 0);
									playerTwoField.Score++;
									break;

								case SDLK_RIGHT:
									p2Block[1].moveRight(playerTwoField.fieldMatrix);
									Mix_PlayChannel(-1, moveSound, 0);
									break;

								case SDLK_LEFT:
									p2Block[1].moveLeft(playerTwoField.fieldMatrix);
									Mix_PlayChannel(-1, moveSound, 0);
									break;

								case SDLK_KP_ENTER: case SDLK_RETURN:
									p2Block[1].hardDrop(playerTwoField.fieldMatrix, playerTwoField.Score);
									break;

								case SDLK_RCTRL:
									if (!p2CanHold) break;
									Mix_PlayChannel(-1, holdSound, 0);
									p2CanHold = false;
									hold(p2Block, p2NextBlock, 5);
									p2Block[0].printNext(1059, 303 - 20, 35);
									p2Block[1].print(1240);
									break;

								}
							}
							switch (e.key.keysym.sym)
							{
							case SDLK_ESCAPE: case SDLK_p:
								Mix_PauseMusic();
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
											Mix_PlayChannel(-1, switchChoicesSound, 0);
											break;
										case SDLK_LEFT: case SDLK_a:
											if (userChoice == 0) userChoice = PAUSE_TOTAL - 1;
											else userChoice--;
											Mix_PlayChannel(-1, switchChoicesSound, 0);
											break;
										case SDLK_SPACE: case SDLK_RETURN:
											pauseModeChosen = userChoice;
											Mix_PlayChannel(-1, switchChoicesSound, 0);
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
									for (int i = 0; i < 3; i++)
									{
										twoPlayerModeScreen.render(0, 0, NULL);
										countDown[i].render(0, 0, NULL);
										SDL_RenderPresent(mainRenderer);
										Mix_PlayChannel(-1, countSound, 0);
										SDL_Delay(1000);
									}
									Mix_PlayChannel(-1, countSound, 0);
									p1TotalTime = SDL_GetTicks();
									p1TotalTime += playerOneField.Time;
									p2TotalTime = SDL_GetTicks();
									p2TotalTime += playerTwoField.Time;
									Mix_ResumeMusic();
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
									Mix_HaltMusic();
									break;
								}
								pauseModeChosen = PAUSE_TOTAL;
								userChoice = 0;
								break;

								
							default:
								break;
							}
							changeMusic(e);
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
						else Mix_PlayChannel(-1, collideSound, 0);

						if (!p2Block[1].collide(playerTwoField.fieldMatrix)) p2Block[1].print(1240);
						else Mix_PlayChannel(-1, collideSound, 0);

						SDL_RenderPresent(mainRenderer);

					}
					if (quitMode) break;

					if (p1Block[1].collide(playerOneField.fieldMatrix) && !p1Lose)
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
					if (p2Block[1].collide(playerTwoField.fieldMatrix) && !p2Lose)
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

					if (playerOneField.checkLose()) p1Lose = true;
					if (playerTwoField.checkLose()) p2Lose = true;

					if (playerOneField.checkLose() && playerTwoField.checkLose())
					{
						Mix_HaltMusic();
						Mix_PlayChannel(-1, gameOverSound, 0);
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

						if (playerOneField.Score > playerTwoField.Score)
						{
							Winner.render(0, 0, NULL);
							Loser.render(960, 0, NULL);
							playerOneField.printScore(532, 703, 60, scoreColor);
							playerTwoField.printScore(1492, 703, 60, loseColor);
						}
						else if (playerTwoField.Score > playerOneField.Score)
						{
							Winner.render(960, 0, NULL);
							Loser.render(0, 0, NULL);
							playerOneField.printScore(532, 703, 60, loseColor);
							playerTwoField.printScore(1492, 703, 60, scoreColor);
						}
						else
						{
							GameOver2.render(0, 0, NULL);
							GameOver2.render(960, 0, NULL);
							playerOneField.printScore(532, 703, 60, scoreColor);
							playerTwoField.printScore(1492, 703, 60, scoreColor);
						}

						SDL_RenderPresent(mainRenderer);
						SDL_Event returnMain;
						returnMain.type = 0;
						SDL_PollEvent(&returnMain);
						while (returnMain.type != SDL_KEYDOWN) SDL_PollEvent(&returnMain);
						playerOneField.reset();
						playerTwoField.reset();
						p1TotalTime = 0;
						p2TotalTime = 0;
						gameModeChosen = CHOOSE_TOTAL;
						break;
					}
				}
				break;

			case CHOOSE_HELP:
				MainScreen.render(0, 0, NULL);
				printButton();
				printMute();
				HelpScreen.render(0, 0, NULL);
				SDL_RenderPresent(mainRenderer);
				SDL_PollEvent(&e);
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) gameModeChosen = CHOOSE_TOTAL;
				break;

			case CHOOSE_QUIT:
				quit = true;
				break;
			}
			
		}
	}

	close();
	closeMusic();
	return 0;
}
