#include "render.h"

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

SDL_Rect BlockRect[BLOCK_TOTAL];
Texture BlockSheet;
Texture Board;
Texture MainScreen;
Texture OptionBox;

Texture::Texture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(string path)
{
	free();

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Couldn't load image " << path << ". Error : " << IMG_GetError() << endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		mTexture = SDL_CreateTextureFromSurface(mainRenderer, loadedSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface" << path << ". Error : " << SDL_GetError << endl;
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	return mTexture != NULL;
}

void Texture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::render(int x, int y, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(mainRenderer, mTexture, clip, &renderQuad);
}

bool initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL couldn't initialize ! Error : " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		mainWindow = SDL_CreateWindow("Let's Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mainWindow == NULL) {
			cout << "Window couldn't be created ! Error : " << SDL_GetError() << endl;
			return false;
		}
		else {
			mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
			if (mainRenderer == NULL) {
				cout << "Renderer couldn't be created ! Error : " << SDL_GetError() << endl;
				return false;
			}
			else {
				SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
					return false;
				}
			}
		}
	}
	return true;
}

void close()
{
	BlockSheet.free();
	MainScreen.free();
	OptionBox.free();


	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;
	mainRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool loadBlock()
{
	if (!BlockSheet.loadFromFile("texture/pastel_block.png"))
	{
		cout << "Failed to load block sheet" << endl;
		return false;
	}
	else
	{
		BlockRect[BLOCK_Z].x = 0;
		BlockRect[BLOCK_Z].y = 0;
		BlockRect[BLOCK_Z].w = BLOCK_SIZE;
		BlockRect[BLOCK_Z].h = BLOCK_SIZE;

		BlockRect[BLOCK_S].x = BLOCK_SIZE;
		BlockRect[BLOCK_S].y = 0;
		BlockRect[BLOCK_S].w = BLOCK_SIZE;
		BlockRect[BLOCK_S].h = BLOCK_SIZE;

		BlockRect[BLOCK_J].x = BLOCK_SIZE * 2;
		BlockRect[BLOCK_J].y = 0;
		BlockRect[BLOCK_J].w = BLOCK_SIZE;
		BlockRect[BLOCK_J].h = BLOCK_SIZE;

		BlockRect[BLOCK_L].x = BLOCK_SIZE * 3;
		BlockRect[BLOCK_L].y = 0;
		BlockRect[BLOCK_L].w = BLOCK_SIZE;
		BlockRect[BLOCK_L].h = BLOCK_SIZE;

		BlockRect[BLOCK_O].x = 0;
		BlockRect[BLOCK_O].y = BLOCK_SIZE;
		BlockRect[BLOCK_O].w = BLOCK_SIZE;
		BlockRect[BLOCK_O].h = BLOCK_SIZE;

		BlockRect[BLOCK_I].x = BLOCK_SIZE;
		BlockRect[BLOCK_I].y = BLOCK_SIZE;
		BlockRect[BLOCK_I].w = BLOCK_SIZE;
		BlockRect[BLOCK_I].h = BLOCK_SIZE;

		BlockRect[BLOCK_T].x = BLOCK_SIZE * 2;
		BlockRect[BLOCK_T].y = BLOCK_SIZE;
		BlockRect[BLOCK_T].w = BLOCK_SIZE;
		BlockRect[BLOCK_T].h = BLOCK_SIZE;

		BlockRect[BLOCK_DEFAULT].x = BLOCK_SIZE * 3;
		BlockRect[BLOCK_DEFAULT].y = BLOCK_SIZE;
		BlockRect[BLOCK_DEFAULT].w = BLOCK_SIZE;
		BlockRect[BLOCK_DEFAULT].h = BLOCK_SIZE;
	}
	return true;
}