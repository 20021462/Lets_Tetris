#include "playerField.h"

Field onePlayerMode;
Field playerOneField;
Field playerTwoField;

void Field::printField(int x)
{
	for (int i = 2; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (fieldMatrix[i][j] == EMPTY) continue;
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

int Field::lineClear()
{
	int lineFull = 0;
	int lineSend = 0;
	//bool getScore = false;
	bool isFull;
	bool canSendFile;
	bool playTrunk = false;
	for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
		isFull = true;
		canSendFile = true;
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (!fieldMatrix[i][j])
			{
				isFull = false;
				canSendFile = false;
			}
			else if (fieldMatrix[i][j] == BLOCK_DEFAULT)
			{
				canSendFile = false;
			}
		}
		if (isFull && canSendFile) {
			fieldDown(i);
			lineFull++;
			i++;
			playTrunk = true;
			//getScore = true;
		}
		else if (isFull && !canSendFile)
		{
			fieldDown(i);
			i++;
			playTrunk = true;
		}
	}
	Line += lineFull;

	if (playTrunk) Mix_PlayChannel(-1, lineClearSound, 0);
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
	return lineFull;
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

void Field::receiveBlock(int a)
{	
	
	for (int tmp = 0; tmp < a; tmp++)
	{	
		
		for (int i = 2; i < BOARD_HEIGHT - 1; i++) {
			for (int j = 0; j < BOARD_WIDTH; j++) {
				fieldMatrix[i][j] = fieldMatrix[i + 1][j];
			}
		}
		for (int i = 0; i < BOARD_WIDTH; i++) {
			fieldMatrix[BOARD_HEIGHT - 1][i] = BLOCK_DEFAULT;
		}
	}
	
	srand(time(NULL));
	int missingBlock = rand() % BOARD_WIDTH;
	for (int i = BOARD_HEIGHT - a; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (j == missingBlock) fieldMatrix[i][j] = EMPTY;
		}
	}

}

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

void Field::printScore(int x, int y, int size, SDL_Color color)
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
	scoreTexture.loadFromRenderedText(scoreText.str().c_str(), color, scoreFont);

	scoreTexture.render(x, y, NULL);
}

unsigned long long int p1SendBlockTime[50] = { 0 };
unsigned long long int p2SendBlockTime[50] = { 0 };

int p1SendBlock[50] = { 0 };
int p2SendBlock[50] = { 0 };

short p1SendBlockPointer = 0;
short p2SendBlockPointer = 0;

void nextBlockSend(unsigned long long int time[], int block[], short &pointer, bool reset)
{
	for (int i = 0; i < 49; i++)
	{
		if (!reset)
		{
			time[i] = time[i + 1];
			block[i] = block[i + 1];
		}
		else
		{
			time[i] = 0;
			block[i] = 0;
		}
	}
	time[49] = 0;
	block[49] = 0;
	if (reset) pointer = 0;
	else pointer--;
}