#include "const.h"
#include "render.h"

class Score
{
public:
	Score();
	~Score();

	int score;
	string name;
	Texture nameTexture;
	Texture scoreTexture;
	SDL_Color color;

	void createTexture();

private:
};

void setColor();

void getScore();

void printHighScore();

extern const short highScoreNumber;
extern Score highScore[];
extern SDL_Color highScoreColor[];
extern TTF_Font* highScoreFont;