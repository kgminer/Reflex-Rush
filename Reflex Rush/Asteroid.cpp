#include "Asteroid.h"

using namespace std;

Asteroid::Asteroid(SDL_Renderer* ren, int screenWidth, int screenHeight, int pos, int difficulty)
{
	asteroidTexture = TextureManager::LoadTexture("assets/rocks_rotated.png", ren);
	if (asteroidTexture == NULL) {
		cout << "Texture failed to load";
	}
	sprite = 0;
	destinationRect.h = 180;
	destinationRect.w = 180;
	destinationRect.x = pos * 180;
	destinationRect.y = -180;
	sourceRect.h = 190;
	sourceRect.w = 180;
	sourceRect.x = 35;
	sourceRect.y = (sprite * 256) + 25;
	xVelocity = 0;
	yVelocity = 1 * difficulty;
	active = false;
	xMax = destinationRect.x + destinationRect.w;
	xMin = destinationRect.x;
	yMax = destinationRect.y + destinationRect.h;
	yMin = destinationRect.y;
	//cout << "Asteriod\n\nXMax : " << xMax << "\nXMin : " << xMin << "\nYMax : " << yMax << "\nYMin : " << yMin << "\n";
}


Asteroid::~Asteroid()
{
	SDL_DestroyTexture(asteroidTexture);
}

void Asteroid::Update()
{
	destinationRect.y += yVelocity;
	yMax = destinationRect.y + destinationRect.h;
	yMin = destinationRect.y;
	int time = SDL_GetTicks();
	int seconds = time / 500;
	sprite = seconds % 8;
	sourceRect.y = (sprite * 256) + 25;
}

void Asteroid::Render(SDL_Renderer * ren)
{
	SDL_RenderCopy(ren, asteroidTexture, &sourceRect, &destinationRect);
}

void Asteroid::setXVelocity(int newVelocity)
{
	xVelocity = newVelocity;
}

void Asteroid::setYVelocity(int newVelocity)
{
	yVelocity = newVelocity;
}

void Asteroid::resetAsteroid()
{
	setActive(false);
	destinationRect.y = -180;
	yMin = destinationRect.y;
}

void Asteroid::setActive(bool newStatus)
{
	active = newStatus;
}

bool Asteroid::getActive()
{
	return active;
}

int Asteroid::getXMax()
{
	return xMax;
}

int Asteroid::getXMin()
{
	return xMin;
}

int Asteroid::getYMax()
{
	return yMax;
}

int Asteroid::getYMin()
{
	return yMin;
}
