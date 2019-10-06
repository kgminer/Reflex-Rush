#include "Asteroid.h"

using namespace std;

Asteroid::Asteroid(SDL_Renderer* ren, int screenWidth, int screenHeight, int pos)
{
	asteroidTexture = TextureManager::LoadTexture("assets/rocks_rotated.png", ren);
	if (asteroidTexture == NULL) {
		cout << "Texture failed to load";
	}
	sprite = 0;
	destinationRect.h = ASTEROID_SCREEN_SIZE_H;
	destinationRect.w = ASTEROID_SCREEN_SIZE_W;
	destinationRect.x = pos * ASTEROID_SCREEN_SIZE_X;
	destinationRect.y = ASTEROID_SCREEN_SIZE_Y;
	sourceRect.h = ASTEROID_IMAGE_H;
	sourceRect.w = ASTEROID_IMAGE_W;
	sourceRect.x = ASTEROID_IMAGE_X;
	sourceRect.y = (sprite * ASTEROID_IMAGE_Y) + ASTEROID_IMAGE_SPACING;
	xVelocity = 0;
	yVelocity = 0;
	active = false;
	xMax = destinationRect.x + destinationRect.w;
	xMin = destinationRect.x;
	yMax = destinationRect.y + destinationRect.h;
	yMin = destinationRect.y;
}


Asteroid::~Asteroid()
{
	SDL_DestroyTexture(asteroidTexture);
}

void Asteroid::Update()
{
	//move the asteroid and update its y coordinates for collision detection
	destinationRect.y += yVelocity;
	yMax = destinationRect.y + destinationRect.h;
	yMin = destinationRect.y;
	//update the sprite image being used to display the asteroid
	int time = SDL_GetTicks();
	int seconds = time / ((int)CONVERT_MS_TO_SEC / 2);
	sprite = seconds % NUMBER_OF_SPRITE_IMAGES;
	sourceRect.y = (sprite * ASTEROID_IMAGE_Y) + ASTEROID_IMAGE_SPACING;
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

void Asteroid::deactivateAsteroid()
{
	//move the asteroid back to its starting place and stop it from being updated
	active = false;
	destinationRect.y = ASTEROID_SCREEN_SIZE_Y;
	yMin = destinationRect.y;
}

void Asteroid::activateAsteroid(int difficulty)
{
	active = true;
	yVelocity = 1 * difficulty;
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
