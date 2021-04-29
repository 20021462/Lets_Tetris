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

bool newHighScore(int newScore);

void rewriteFile();

void nameInput(string& name, SDL_Event e);

extern const short highScoreNumber;
extern Score highScore[];
extern SDL_Color highScoreColor[];
extern TTF_Font* highScoreFont;
extern TTF_Font* textInput;

extern Score* pointer;
