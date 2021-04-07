#include "render.h"
#include "const.h"
#include "block.h"

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

SDL_Rect BlockRect[BLOCK_TOTAL];
Texture BlockSheet;
Texture Board;

int player1Board[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

void print()
{
	for (int i = 4; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			if (player1Board[i][j] == 0) continue;
			if (player1Board[i][j] > BLOCK_TOTAL) BlockSheet.render(150 + 40 * j, 50 + 40 * (i - 4), &BlockRect[player1Board[i][j] - BLOCK_TOTAL]);
			else BlockSheet.render(150 + 40 * j, 50 + 40 * (i - 4), &BlockRect[player1Board[i][j]]);
		}
	}
}

void generateBlock(int BlockType)
{
	switch (BlockType)
	{
		case BLOCK_Z : 
			player1Board[0][5] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[1][5] = BlockType;
			player1Board[2][4] = BlockType;
			break;

		case BLOCK_S:
			player1Board[0][4] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[1][5] = BlockType;
			player1Board[2][5] = BlockType;
			break;

		case BLOCK_J:
			player1Board[0][5] = BlockType;
			player1Board[1][5] = BlockType;
			player1Board[2][5] = BlockType;
			player1Board[2][4] = BlockType;
			break;

		case BLOCK_L:
			player1Board[0][4] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[2][4] = BlockType;
			player1Board[2][5] = BlockType;
			break;

		case BLOCK_I:
			player1Board[0][4] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[2][4] = BlockType;
			player1Board[3][4] = BlockType;
			break;

		case BLOCK_O:
			player1Board[0][4] = BlockType;
			player1Board[0][5] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[1][5] = BlockType;
			break;

		case BLOCK_T:
			player1Board[0][4] = BlockType;
			player1Board[1][3] = BlockType;
			player1Board[1][4] = BlockType;
			player1Board[1][5] = BlockType;
			break;
	}
}

/*void gravity()
{
	for (int i = 22; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (player1Board[i][j] > EMPTY )
		}
	}
}*/

int main(int argc, char* args[])
{
	long long time_ = 1;
	int moveTime = 1;
	int startTIme = 0;

	srand(time(0));
	int tmp = rand() % 7 + 1;
	generateBlock(tmp);

	if (!initSDL())
	{
		cout << "Failed to initialize!\n";
	}
	else
	{
		if (!Board.loadFromFile("texture/Board.png"))
		{
			cout << "Failed to load board" << endl;
		}
		else
		{
			if (!loadBlock())
			{
				cout << "Failed to load block sheet" << endl;
			}
			else
			{
				bool quit = false;
				SDL_Event e;

				while (!quit)
				{
<<<<<<< Updated upstream
					while (SDL_PollEvent(&e) != 0)
=======
					SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(mainRenderer);

					int tmp = rand() % 7 + 1;
					block.generate(tmp);

					while (!block.collide())
					{	
						
						if (SDL_GetTicks()/1000 > time_)
						{	
							time_ += moveTime;
							block.move(0, 1);
						}
						Board.render(145, 45, NULL);
						print();
						SDL_Event e;
						SDL_PollEvent(&e);
						block.control(e);
						e.key.keysym.sym = SDLK_DOWN;
						block.print();
						SDL_RenderPresent(mainRenderer);
						//SDL_Delay(1000 / FPS);
					}
					unite(block);

					/*while (SDL_PollEvent(&e) != 0)
>>>>>>> Stashed changes
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
					}

					SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(mainRenderer);

					while (player1Board[23][4] != 1) {
						for (int i = 22; i >= 0; i--) {
							for (int j = 0; j < 10; j++) {
								player1Board[i + 1][j] = player1Board[i][j];
								if (i == 0) player1Board[i][j] = 0;
							}
						}
						Board.render(145, 45, NULL);
						print();
						SDL_RenderPresent(mainRenderer);
						SDL_Delay(500);
					}
				}
			}

		}
	}

	close();
	return 0;
}
