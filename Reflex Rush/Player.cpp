#include "Player.h"

using namespace std;

Player::Player(SDL_Renderer* ren, int screenWidth, int screenHeight)
{
	playerTexture = TextureManager::LoadTexture("assets/SF04.png", ren);
	if (playerTexture == NULL) {
		cout << "Texture failed to load";
	}
	destinationRect.h = 128;
	destinationRect.w = 128;
	destinationRect.x = (screenWidth / 2) - 128;
	destinationRect.y = screenHeight - 128;
	sourceRect.h = 180;
	sourceRect.w = 135;
	sourceRect.x = 60;
	sourceRect.y = 30;
	xVelocity = 0;
	yVelocity = 0;
	xMax = destinationRect.x + destinationRect.w;
	xMin = destinationRect.x;
	yMax = destinationRect.y + destinationRect.h; 
	yMin = destinationRect.y;
	isAlive = true;
	//cout << "Player\n\nXMax : " << xMax << "\nXMin : " << xMin << "\nYMax : " << yMax << "\nYMin : " << yMin << "\n";
}


Player::~Player()
{
}

int Player::Update(int screenWidth, int screenHeight, class Asteroid *asteroidLayer[][8])
{
	int status;
	move(screenWidth, screenHeight);
	status = checkCollision(asteroidLayer);
	return status;
}

void Player::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, playerTexture, &sourceRect, &destinationRect);
}

void Player::setXVelocity(int newVelocity)
{
	xVelocity = newVelocity;
}

void Player::setYVelocity(int newVelocity)
{
	yVelocity = newVelocity;
}

void Player::move(int screenWidth, int screenHeight)
{
	destinationRect.x += xVelocity;
	destinationRect.y += yVelocity;
	xMax = destinationRect.x + destinationRect.w;
	xMin = destinationRect.x;
	yMax = destinationRect.y + destinationRect.h;
	yMin = destinationRect.y;

	if (destinationRect.x < 0) {
		destinationRect.x = 0;
	}
	else if (destinationRect.x > screenWidth - destinationRect.w) {
		destinationRect.x = screenWidth - destinationRect.w;
	}

	if (destinationRect.y < 0) {
		destinationRect.y = 0;
	}
	else if (destinationRect.y > screenHeight - destinationRect.h) {
		destinationRect.y = screenHeight - destinationRect.h;
	}
}

void Player::centerShip(int screenWidth, int screenHeight)
{
	destinationRect.x = (screenWidth / 2) - 128;
	destinationRect.y = screenHeight - 128;
}

void Player::print()
{
	cout << "Player\n\nXMax : " << xMax << "\nXMin : " << xMin << "\nYMax : " << yMax << "\nYMin : " << yMin << "\n";
}

int Player::checkCollision(class Asteroid *asteroidLayer[][8])
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++) {
			if (asteroidLayer[i][j]->getActive() == false) {
				continue;
			}
			else {
				if (xMax < asteroidLayer[i][j]->getXMin() || xMin > asteroidLayer[i][j]->getXMax()) {
					continue;
				}

				if (yMax < asteroidLayer[i][j]->getYMin() || yMin > asteroidLayer[i][j]->getYMax()) {
					continue;
				}

				setXVelocity(0);
				setYVelocity(0);
				return 1;
			}
		}
	}
	return 0;
}
