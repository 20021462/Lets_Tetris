#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 900;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 24;

void copyMatrix(int matrix[4][4], int temp[4][4], int size);
void horizontalReflectioin(int matrix[4][4], int size);
void transpose(int matrix[4][4], int size);