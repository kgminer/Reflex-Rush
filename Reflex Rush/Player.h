#pragma once
#include "GameManager.h"

class Player
{
public:
	Player(SDL_Renderer* ren, int screenWidth, int screenHeight);
	~Player();
	int Update(int screenWidth, int screenHeight, class Asteroid *asteroidLayer[][8]);
	void Render(SDL_Renderer* ren);
	void setXVelocity(int newVelocity);
	void setYVelocity(int newVelocity);
	void move(int screenWidth, int screenHeight);
	void centerShip(int screenWidth, int screenHeight);
	void print();
	int checkCollision(class Asteroid *asteroidLayer[][8]);

private:
	int xVelocity, yVelocity, xMax, xMin, yMax, yMin;
	bool isAlive;
	SDL_Rect sourceRect, destinationRect;
	SDL_Texture *playerTexture;
};

