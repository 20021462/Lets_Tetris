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
		MainScreen.loadFromFile("texture/homescreen.png");
		OptionBox.loadFromFile("texture/option_box.png");
		Board.loadFromFile("texture/pastel_pf.png");
		loadBlock();

		bool quit = false;
		SDL_Event e;

		while (!quit)
		{
			SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(mainRenderer);

			MainScreen.render(0, 0, NULL);
			OptionBox.render(785, 600, NULL);
			SDL_RenderPresent(mainRenderer);
			SDL_Delay(5000);

			block.generate(rand() % 7 + 1);

			while (!block.collide())
			{	
						
				if (SDL_GetTicks() / 1000 > time_)
				{	
					time_ += Time;
					block.move(0, 1);
				}
						
				Board.render(750, 135, NULL);
				printField();
				SDL_PollEvent(&e);
				if (e.type == SDL_QUIT)
				{
					quit = true;
					break;
				}
				else if (e.type == SDL_KEYDOWN)
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
				block.print();
				SDL_RenderPresent(mainRenderer);

				if (lineClear()) 
				{
					Board.render(750, 135, NULL);
					block.print();
					SDL_RenderPresent(mainRenderer);
				}
			}
					unite(block);
		}
	}

	close();
	return 0;
}
