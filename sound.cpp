#include "sound.h"
#include "render.h"
#include <sstream>

Mix_Chunk* gameOverSound = NULL;
Mix_Chunk* moveSound = NULL;
Mix_Chunk* countSound = NULL;
Mix_Chunk* rotateSound = NULL;
Mix_Chunk* lineClearSound = NULL;
Mix_Chunk* holdSound = NULL;
Mix_Chunk* collideSound = NULL;
Mix_Chunk* switchChoicesSound = NULL;

Mix_Music* ingameMusic[10];
Mix_Music* homeScreenMusic = NULL;

bool mute = false;


bool loadMedia()
{
	bool success = true;
	
	for (int i = 0; i <= 3; i++)
	{
		stringstream path;
		path << "music/ingameMusic" << i << ".mp3";
		ingameMusic[i] = Mix_LoadMUS(path.str().c_str());
		if (ingameMusic[i] == NULL)
		{
			printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
	}

	homeScreenMusic = Mix_LoadMUS("music/homeScreenMusicWibu.flac");
	if (homeScreenMusic == NULL)
	{
		printf("Failed to load homeScreenMusic! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

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

	collideSound = Mix_LoadWAV("music/collideSound.wav");
	if (collideSound == NULL)
	{
		printf("Failed to load collide sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	switchChoicesSound = Mix_LoadWAV("music/switchChoicesSound.wav");
	if (collideSound == NULL)
	{
		printf("Failed to load switch choices sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void closeMusic()
{
	Mix_FreeChunk(gameOverSound);
	Mix_FreeChunk(moveSound);
	Mix_FreeChunk(countSound);
	Mix_FreeChunk(rotateSound);
	Mix_FreeChunk(lineClearSound);
	Mix_FreeChunk(collideSound);
	collideSound = NULL;
	lineClearSound = NULL;
	gameOverSound = NULL;
	moveSound = NULL;
	countSound = NULL;
	rotateSound = NULL;

	Mix_FreeMusic(homeScreenMusic);
	homeScreenMusic = NULL;

	for (int i = 0; i <= 3; i++)
	{
		Mix_FreeMusic(ingameMusic[i]);
		ingameMusic[i] = NULL;
	}
}

void changeMusic(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN )
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_0:
			Mix_PlayMusic(ingameMusic[0], -1);
			break;

		case SDLK_1:
			Mix_PlayMusic(ingameMusic[1], -1);
			break;

		case SDLK_2:
			Mix_PlayMusic(ingameMusic[2], -1);
			break;

		case SDLK_3:
			Mix_PlayMusic(ingameMusic[1], -1);
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
		}
	}
}

void printMute()
{
	if (mute) Mute.render(1840, 30, NULL);
	else Unmute.render(1840, 30, NULL);
}