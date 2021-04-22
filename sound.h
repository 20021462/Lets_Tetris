#include "Const.h"

extern Mix_Chunk* gameOverSound;
extern Mix_Chunk* moveSound;
extern Mix_Chunk* countSound;
extern Mix_Chunk* rotateSound;
extern Mix_Chunk* lineClearSound;
extern Mix_Chunk* holdSound;
extern Mix_Chunk* collideSound;
extern Mix_Chunk* switchChoicesSound;

extern Mix_Music* ingameMusic[10];
extern Mix_Music* homeScreenMusic;

extern bool mute;

bool loadMedia();

void closeMusic();

void changeMusic(SDL_Event e);

void printMute();