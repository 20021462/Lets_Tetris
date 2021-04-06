#include "render.h"
#include "const.h"
#include "block.h"

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

SDL_Rect BlockRect[BLOCK_TOTAL];
Texture BlockSheet;
Texture Board;

int player1Field[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

void print()
{
	for (int i = 4; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			if (player1Field[i][j] == 0) continue;
			if (player1Field[i][j] > BLOCK_TOTAL) BlockSheet.render(150 + 40 * j, 50 + 40 * (i - 4), &BlockRect[player1Field[i][j] - BLOCK_TOTAL]);
			else BlockSheet.render(150 + 40 * j, 50 + 40 * (i - 4), &BlockRect[player1Field[i][j]]);
		}
	}
}

int main(int argc, char* args[])
{

	srand(time(0));
	
	Block block;

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

				while (!quit)
				{
					SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(mainRenderer);

					int tmp = rand() % 7 + 1;
					block.generate(tmp);

					while (!block.collide())
					{
						block.move(0, 1);
						Board.render(145, 45, NULL);
						print();
						SDL_Event e;
						SDL_PollEvent(&e);
						block.control(e);
						e.type = NULL;
						block.print();
						SDL_RenderPresent(mainRenderer);
						SDL_Delay(1000 / FPS);
					}
					unite(block);

					/*while (SDL_PollEvent(&e) != 0)
					{
						block.gravity();
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
						else if (e.type == SDL_KEYDOWN)
						{
							block.control(e);
						}
						Board.render(145, 45, NULL);
						print();
						block.print();
						SDL_RenderPresent(mainRenderer);
						SDL_Delay(1000 / FPS);
						if (block.collide()) unite(block);
					}*/
				}
			}

		}
	}

	close();
	return 0;
}
