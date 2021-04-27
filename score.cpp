#include "score.h"

const short highScoreNumber = 5;
Score highScore[highScoreNumber];
SDL_Color highScoreColor[highScoreNumber];
TTF_Font* highScoreFont = NULL; 


Score::Score()
{
}

Score::~Score()
{
}

void Score::createTexture()
{
	stringstream scoreText;
	scoreText << score;

	scoreTexture.loadFromRenderedText(scoreText.str().c_str(), color, highScoreFont);
	nameTexture.loadFromRenderedText(name, color, highScoreFont);
}

void setColor()
{
	highScoreColor[0] = { 193, 56, 50 };
	highScoreColor[1] = { 151, 197, 235 };
	highScoreColor[2] = { 245, 207, 71 };
	highScoreColor[3] = { 206, 169, 141 };
	highScoreColor[4] = { 52, 182, 228 };

	highScoreFont = TTF_OpenFont("font/gilroy-extrabold.otf", 50);
}

void getScore()
{
	ifstream file("highscore.txt");
	for (int i = 0; i < highScoreNumber; i++)
	{
		file >> highScore[i].name;
		file >> highScore[i].score;
		highScore[i].color = highScoreColor[i];
		highScore[i].createTexture();
	}
}

void printHighScore()
{
	for (int i = 0; i < highScoreNumber; i++)
	{
		highScore[i].nameTexture.render(680, 310 + i * 130, NULL);
		highScore[i].scoreTexture.render(1365 - highScore[i].scoreTexture.mWidth, 310 + i * 130, NULL);
	}
}

