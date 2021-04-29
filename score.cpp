#include "score.h"
#include "sound.h"

const short highScoreNumber = 5;
Score highScore[highScoreNumber];
SDL_Color highScoreColor[highScoreNumber];
TTF_Font* highScoreFont = NULL; 
TTF_Font* textInput = NULL;

Score* pointer;

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
	textInput = TTF_OpenFont("font/gilroy-extrabold.otf", 50);
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
	file.close();
}

void printHighScore()
{
	for (int i = 0; i < highScoreNumber; i++)
	{
		highScore[i].nameTexture.render(680, 310 + i * 130, NULL);
		highScore[i].scoreTexture.render(1365 - highScore[i].scoreTexture.mWidth, 310 + i * 130, NULL);
	}
}

bool newHighScore(int newScore)
{
	for (int i = 0; i < highScoreNumber; i++)
	{
		if (newScore > highScore[i].score)
		{
			for (int j = highScoreNumber - 1; j > i; j--)
			{
				highScore[j].score = highScore[j - 1].score;
				highScore[j].name = highScore[j - 1].name;
			}
			highScore[i].score = newScore;
			pointer = &highScore[i];
			return true;
		}
	}
	return false;
}

void rewriteFile()
{
	fstream file;
	file.open("highscore.txt", ios::out | ios::trunc);
	for (int i = 0; i < highScoreNumber; i++)
	{
		file << highScore[i].name << ' ' << highScore[i].score << endl;
	}
	file.close();
}

void nameInput(string &name, SDL_Event e)
{
	Texture inputTextTexture;
	inputTextTexture.loadFromRenderedText(name.c_str(), scoreColor, textInput);
	bool renderText = false;
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_BACKSPACE && name.length() > 0)
		{
			Mix_PlayChannel(-1, moveSound, 0);
			name.pop_back();
			renderText = true;
		}
		else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
		{
			SDL_SetClipboardText(name.c_str());
		}
		else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
		{
			name = SDL_GetClipboardText();
			renderText = true;
		}
	}
	else if (e.type == SDL_TEXTINPUT)
	{
		if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')) && name.length() <= 13 && e.text.text[0] != ' ')
		{
			Mix_PlayChannel(-1, moveSound, 0);
			name += e.text.text;
			renderText = true;
		}
	}
	if (renderText)
	{
		if (name != "")
		{
			inputTextTexture.loadFromRenderedText(name.c_str(), scoreColor, textInput);
		}
		else
		{
			inputTextTexture.loadFromRenderedText(" ", scoreColor, textInput);
		}
	}
	inputTextTexture.render(945, 700, NULL);
}