#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>

using namespace std;



//bool initSDL();
//
//void close();
//
//bool loadBlock();

class Texture
{
public:
	Texture();

	~Texture();

	bool loadFromFile(string path, SDL_Renderer* Renderer);



	void free();

	void render(int x, int y, SDL_Rect* clip, SDL_Renderer* Renderer);



private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

};



//void print();
//
//void generateBlock(int BlockType);
