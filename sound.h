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

extern bool music;

bool loadMedia();

void stopMusic();

void playMusic(Mix_Music* name);

void closeMusic();