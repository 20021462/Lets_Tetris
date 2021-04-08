#include "render.h"
#include "const.h"
#include "block.h"
#include "playerField.h"

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
		if (!Board.loadFromFile("texture/pastel_pf.png"))
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

					
					block.generate(rand() % 7 + 1);

					while (!block.collide())
					{	
						
						if (SDL_GetTicks() / 1000 > time_)
						{	
							time_ += Time;
							block.move(0, 1);
						}
						
						Board.render(145, 45, NULL);
						printField();
						SDL_Event e;
						SDL_PollEvent(&e);
						block.control(e);
						e.key.keysym.sym = NULL;
						block.print();
						SDL_RenderPresent(mainRenderer);
						if (lineClear()) {
							Board.render(145, 45, NULL);
							block.print();
							SDL_RenderPresent(mainRenderer);
						}
						
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
