#pragma once
#include "GameManager.h"

class Asteroid
{
public:
	Asteroid(SDL_Renderer* ren, int screenWidth, int screenHeight, int pos, int difficulty);
	~Asteroid();
	void Update();
	void Render(SDL_Renderer* ren);
	void setXVelocity(int newVelocity);
	void setYVelocity(int newVelocity);
	int getXMax();
	int getXMin();
	int getYMax();
	int getYMin();
private:
	int xVelocity, yVelocity, xMax, xMin, yMax, yMin, sprite;
	SDL_Rect sourceRect, destinationRect;
	SDL_Texture *asteroidTexture;
};

