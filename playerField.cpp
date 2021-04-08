#include "playerField.h"

int player1Field[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
int Level = 1;
int Line = 0;
int Point = 0;
double Time = 1;

void printField()
{
	for (int i = 2; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (player1Field[i][j] == 0) continue;
			else BlockSheet.render(START_WIDTH + BLOCK_SIZE * j, START_HEIGHT + BLOCK_SIZE * (i - 2), &BlockRect[player1Field[i][j]]);

		}
	}
}

void unite(Block& block)
{
	block.move(0, -1);
	for (int i = 0; i < block.size; i++)
	{
		for (int j = 0; j < block.size; j++)
		{
			if (block.matrix[i][j])
			{
				player1Field[block.y_ + i][block.x_ + j] = block.matrix[i][j];
			}
		}
	}

}

void fieldDown(int line)
{
	for (int i = line - 1; i > 0; i--) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			player1Field[i + 1][j] = player1Field[i][j];
		}
	}
	for (int i = 0; i < BOARD_WIDTH; i++) {
		player1Field[0][i] = 0;
	}
}

bool lineClear()
{
	int lineFull = 0;
	bool getPoint = false;
	bool isFull = true;
	for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
		isFull = true;
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (!player1Field[i][j]) isFull = false;
		}
		if (isFull) {
			fieldDown(i);
			lineFull++;
			i++;
			getPoint = true;
		}
	}
	Line += lineFull;
	switch (lineFull)
	{
	case 1:
		Point += 1;
		break;
	case 2:
		Point += 3;
		break;
	case 3:
		Point += 5;
		break;
	case 4:
		Point += 8;
		break;
	}
	Level = Point / 10 + 1;
	Time = pow(0.8 - (Level - 1) * 0.007, Level - 1);
	return getPoint;
}
