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
	bool getScore = false;
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
			getScore = true;
		}
	}
	Line += lineFull;
	switch (lineFull)
	{
	case 1:
		Score += 100 * Level;
		break;
	case 2:
		Score += 300 * Level;
		break;
	case 3:
		Score += 500 * Level;
		break;
	case 4:
		Score += 800 * Level;
		break;
	}
	Level = min(Line / 5 + 1, 15);
	Time = pow(0.8 - (Level - 1) * 0.007, Level - 1) * 1000;
	return getScore;
}

void Field::shade(Block& block, int x)
{
	Block temp = block;
	int empty;
	temp.hardDrop(fieldMatrix, empty);
	temp.y_--;
	temp.printShade(x);
}

bool Field::checkLose()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (fieldMatrix[BOARD_HEIGHT - 20][i])
		{
			return true;
		}
	}
	return false;
}

void Field::reset()
{
	Level = 1;
	Line = 0;
	Score = 0;
	Time = 1000;
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			fieldMatrix[i][j] = 0;
		}
	}
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

void Field::getStat(int x)
{
	stringstream scoreText;
	stringstream lineText;
	stringstream levelText;
	
	scoreText.str("");
	lineText.str("");
	levelText.str("");

	if (Score < 100000) scoreText << 0;
	if (Score < 10000) scoreText << 0;
	if (Score < 1000) scoreText << 0;
	if (Score < 100) scoreText << 0;
	if (Score < 10) scoreText << 0;

	if (Line < 100) lineText << 0;
	if (Line < 10) lineText << 0;

	if (Level < 100) levelText << 0;

	scoreText << Score;
	lineText << Line;
	levelText << Level;

	scoreTexture.loadFromRenderedText(scoreText.str().c_str(), scoreColor, gFont);
	lineTexture.loadFromRenderedText(lineText.str().c_str(), lineColor, gFont);
	levelTexture.loadFromRenderedText(levelText.str().c_str(), levelColor, gFont);

	scoreTexture.render(onePlayerModeScreen.mWidth / 4 + 49 + x, 538, NULL);
	levelTexture.render(onePlayerModeScreen.mWidth / 4 + 105 + x, 692, NULL);
	lineTexture.render(onePlayerModeScreen.mWidth / 4 + 92 + x, 855, NULL);
}

void Field::printScore(int x, int y, int size)
{
	stringstream scoreText;

	if (Score < 100000) scoreText << 0;
	if (Score < 10000) scoreText << 0;
	if (Score < 1000) scoreText << 0;
	if (Score < 100) scoreText << 0;
	if (Score < 10) scoreText << 0;
	scoreText << Score;

	TTF_Font* scoreFont = NULL;
	scoreFont = TTF_OpenFont("font/gilroy-extrabold.otf", size);
	scoreTexture.loadFromRenderedText(scoreText.str().c_str(), scoreColor, scoreFont);

	scoreTexture.render(x, y, NULL);
}