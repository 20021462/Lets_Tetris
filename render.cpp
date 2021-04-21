#include "render.h"


Mix_Chunk* gameOverSound = NULL;
Mix_Chunk* moveSound = NULL;
Mix_Chunk* countSound = NULL;
Mix_Chunk* rotateSound = NULL;
Mix_Chunk* lineClearSound = NULL;
Mix_Chunk* holdSound = NULL;

Mix_Music* ingameMusic = NULL;
Mix_Music* homeScreenMusic=NULL;

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

SDL_Rect BlockRect[BLOCK_TOTAL];
Texture BlockSheet;
Texture ShadeSheet;
Texture MainScreen;
Texture HelpScreen;
Texture GameOver;

Texture GameOver2;
Texture Winner;
Texture Loser;

Texture onePlayerModeScreen;
Texture twoPlayerModeScreen;
Texture pauseBackground;
Texture countDown[3];

TTF_Font* gFont = NULL;
SDL_Color scoreColor;
SDL_Color levelColor;
SDL_Color lineColor;
SDL_Color loseColor;

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

bool Texture::loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font *font)
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(mainRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
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

void Texture::render(int x, int y, SDL_Rect* clip, int size)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	if (size)
	{
		renderQuad.w = size;
		renderQuad.h = size;
	}
	SDL_RenderCopy(mainRenderer, mTexture, clip, &renderQuad);
}

bool initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					return false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					return false;
				}
			}
		}
	}


	return true;
}

void loadTexture()
{
	MainScreen.loadFromFile("texture/mainScreen.png");
	HelpScreen.loadFromFile("texture/help_screen.png");
	GameOver.loadFromFile("texture/Gameover.png");
	GameOver2.loadFromFile("texture/Yourscore.png");
	Winner.loadFromFile("texture/Winner.png");
	Loser.loadFromFile("texture/Loser.png");
	onePlayerModeScreen.loadFromFile("texture/1playerPlayingScreen.png");
	twoPlayerModeScreen.loadFromFile("texture/2playerPlayingScreen.png");
	pauseBackground.loadFromFile("texture/pauseBackground.png");
	countDown[0].loadFromFile("texture/3.png");
	countDown[1].loadFromFile("texture/2.png");
	countDown[2].loadFromFile("texture/1.png");

}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load music
	ingameMusic = Mix_LoadMUS("music/ingameMusic.wav");
	if (ingameMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	homeScreenMusic = Mix_LoadMUS("music/homeScreenMusic.wav");
	if (homeScreenMusic == NULL)
	{
		printf("Failed to load homeScreenMusic! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load sound effects

	gameOverSound = Mix_LoadWAV("music/gameOver.wav");
	if (gameOverSound == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	moveSound = Mix_LoadWAV("music/Move.wav");
	if (moveSound == NULL)
	{
		printf("Failed to load move sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	countSound = Mix_LoadWAV("music/3,2,1.wav");
	if (countSound == NULL)
	{
		printf("Failed to load count sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	rotateSound = Mix_LoadWAV("music/rotate.wav");
	if (rotateSound == NULL)
	{
		printf("Failed to load rotate sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	lineClearSound = Mix_LoadWAV("music/lineClear.wav");
	if (lineClearSound == NULL)
	{
		printf("Failed to load lineClear sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	holdSound = Mix_LoadWAV("music/holdSound.wav");
	if (lineClearSound == NULL)
	{
		printf("Failed to load hold sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void stopMusic()
{
	Mix_HaltMusic();
	music = false;
}

void playMusic(Mix_Music* name)
{
	if(!music) Mix_PlayMusic(name, -1);
	music = true;;
}

void close()
{
	BlockSheet.free();
	ShadeSheet.free();
	MainScreen.free();
	HelpScreen.free();
	GameOver.free();
	GameOver2.free();
	Winner.free();
	Loser.free();
	onePlayerModeScreen.free();
	twoPlayerModeScreen.free();
	pauseBackground.free();

	TTF_CloseFont(gFont);
	gFont = NULL;

	Mix_FreeChunk(gameOverSound);
	Mix_FreeChunk(moveSound);
	Mix_FreeChunk(countSound);
	Mix_FreeChunk(rotateSound);
	Mix_FreeChunk(lineClearSound);
	lineClearSound = NULL;
	gameOverSound = NULL;
	moveSound = NULL;
	countSound = NULL;
	rotateSound = NULL;

	Mix_FreeMusic(homeScreenMusic);
	Mix_FreeMusic(ingameMusic);
	ingameMusic = NULL;
	homeScreenMusic = NULL;


	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;
	mainRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

bool loadStat()
{
	bool success = true;

	gFont = TTF_OpenFont("font/gilroy-extrabold.otf", 45);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		scoreColor = { 252, 71, 91 };
		levelColor = { 252, 215, 75 };
		lineColor = { 145, 197, 235 };
		loseColor = { 255, 255, 255 };
	}

	return success;
}

bool loadBlock()
{
	if (!BlockSheet.loadFromFile("texture/pastel_block.png")||!ShadeSheet.loadFromFile("texture/pastel_shade.png"))
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
