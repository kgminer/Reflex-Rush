#pragma once
#include "GameManager.h"

class Asteroid
{
public:
	Asteroid(SDL_Renderer* ren, int screenWidth, int screenHeight, int pos);
	~Asteroid();
	void Update();
	void Render(SDL_Renderer* ren);
	void setXVelocity(int newVelocity);
	void setYVelocity(int newVelocity);
	void deactivateAsteroid();
	void activateAsteroid(int difficulty);
	void setActive(bool newStatus);
	bool getActive();
	int getXMax();
	int getXMin();
	int getYMax();
	int getYMin();
private:
	int xVelocity, yVelocity, xMax, xMin, yMax, yMin, sprite;
	bool active;
	SDL_Rect sourceRect, destinationRect;
	SDL_Texture *asteroidTexture;
};

