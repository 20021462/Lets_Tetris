#pragma once
#include "const.h"
#include "block.h"

extern int player1Field[BOARD_HEIGHT][BOARD_WIDTH];
extern int Level;
extern int Line;
extern int Point;
extern int Time;

void printField();
void unite(Block& block);
void fieldDown(int line);
bool lineClear();


