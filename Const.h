#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 22;

const int START_WIDTH = 755;
const int START_HEIGHT = 140;

const int BLOCK_SIZE = 40;


const int FPS = 4;

void copyMatrix(int matrix[4][4], int temp[4][4], int size);
void horizontalReflectioin(int matrix[4][4], int size);
void transpose(int matrix[4][4], int size);