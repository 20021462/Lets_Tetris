#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <sstream>

using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 22;

const int START_WIDTH = 755;
const int START_HEIGHT = 140;

const int BLOCK_SIZE = 40;

extern unsigned long long int totalTime;
extern unsigned long long int p1TotalTime;
extern unsigned long long int p2TotalTime;
extern int tmpLine1;
extern int tmpLine2;
extern short int p1Place;
extern short int p2Place;
extern bool p1CanHold;
extern bool p2CanHold;
extern bool p1Lose;
extern bool p2Lose;

void copyMatrix(int matrix[4][4], int temp[4][4], int size);
void horizontalReflectioin(int matrix[4][4], int size);
void transpose(int matrix[4][4], int size);