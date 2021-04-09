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
				SDL_Event e;

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
						SDL_PollEvent(&e);
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
						//e.key.keysym.sym = NULL;
						block.print();
<<<<<<< HEAD
<<<<<<< HEAD
						shade(block);
=======
>>>>>>> parent of 4ddebcf (8:38 9/4/21)
=======
>>>>>>> parent of 4ddebcf (8:38 9/4/21)
						SDL_RenderPresent(mainRenderer);
						if (lineClear()) {
							Board.render(145, 45, NULL);
							block.print();
							SDL_RenderPresent(mainRenderer);
						}
						
					}
					
					unite(block);
				}
			}

		}
	}

	close();
	return 0;
}
