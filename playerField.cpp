#include "playerField.h"

Field onePlayerMode;
Field playerOneField;
Field playerTwoField;

void Field::printField(int x)
{
	for (int i = 2; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (fieldMatrix[i][j] == 0) continue;
			else BlockSheet.render(x + BLOCK_SIZE * j, START_HEIGHT + BLOCK_SIZE * (i - 2), &BlockRect[fieldMatrix[i][j]]);

		}
	}
}

void Field::unite(Block& block)
{
	block.move(0, -1);
	for (int i = 0; i < block.size; i++)
	{
		for (int j = 0; j < block.size; j++)
		{
			if (block.matrix[i][j])
			{
				fieldMatrix[block.y_ + i][block.x_ + j] = block.matrix[i][j];
			}
		}
	}

}

void Field::fieldDown(int line)
{
	for (int i = line - 1; i > 0; i--) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			fieldMatrix[i + 1][j] = fieldMatrix[i][j];
		}
	}
	for (int i = 0; i < BOARD_WIDTH; i++) {
		fieldMatrix[0][i] = 0;
	}
}

bool Field::lineClear()
{
	int lineFull = 0;
	bool getPoint = false;
	bool isFull = true;
	for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
		isFull = true;
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (!fieldMatrix[i][j]) isFull = false;
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
	double tmp = max(pow(0.8 - (Level - 1) * 0.007, Level - 1), 0.00706);
	Time = tmp * 1000;
	return getPoint;
}

void Field::shade(Block& block, int x)
{
	Block temp = block;
	
	temp.hardDrop(fieldMatrix);
	temp.y_--;
	temp.printShade(x);
}

bool Field::lose()
{
	bool lose = false;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (fieldMatrix[BOARD_HEIGHT - 20][i])
		{
			Level = 1;
			Line = 0;
			Point = 0;
			Time = 1000;
			lose = true;
			break;
		}
	}
	if (lose == true)
	{
		for (int i = 0; i < BOARD_HEIGHT; i++) {
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				fieldMatrix[i][j] = 0;
			}
		}
	}
	return lose;
}

/*void Field::sendBlock(int line)
{
	int tmp = line;
	while (tmp > 0)
	{
		for (int i = 2; i < BOARD_HEIGHT - 1; i++) {
			for (int j = 0; j < BOARD_WIDTH; j++) {
				fieldMatrix[i][j] = fieldMatrix[i + 1][j];
			}
		}
		for (int i = 0; i < BOARD_WIDTH; i++) {
			fieldMatrix[BOARD_HEIGHT - 1][i] = EMPTY;
		}
		tmp--;
	}
	srand(time(0));
	int missingBlock = rand() % BOARD_HEIGHT;
	for (int i = BOARD_HEIGHT - line; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			if (j == missingBlock) continue;
			fieldMatrix[i][j] = BLOCK_DEFAULT;
		}
	}

}*/
