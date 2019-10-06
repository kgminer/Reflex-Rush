#include "Player.h"

using namespace std;

Player::Player(SDL_Renderer* ren, int screenWidth, int screenHeight)
{
	playerTexture = TextureManager::LoadTexture("assets/SF04.png", ren);
	if (playerTexture == NULL) {
		cout << "Texture failed to load";
	}
	destinationRect.h = PLAYER_SCREEN_SIZE_H;
	destinationRect.w = PLAYER_SCREEN_SIZE_W;
	destinationRect.x = (screenWidth / 2) - PLAYER_SCREEN_SIZE_X_SPACING;
	destinationRect.y = screenHeight - PLAYER_SCREEN_SIZE_Y_SPACING;
	sourceRect.h = PLAYER_IMAGE_H;
	sourceRect.w = PLAYER_IMAGE_W;
	sourceRect.x = PLAYER_IMAGE_X;
	sourceRect.y = PLAYER_IMAGE_Y;
	xVelocity = 0;
	yVelocity = 0;
	xMax = destinationRect.x + destinationRect.w;
	xMin = destinationRect.x;
	yMax = destinationRect.y + destinationRect.h; 
	yMin = destinationRect.y;
	isAlive = true;
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
	destinationRect.x = (screenWidth / 2) - PLAYER_SCREEN_SIZE_X_SPACING;
	destinationRect.y = screenHeight - PLAYER_SCREEN_SIZE_Y_SPACING;
}

int Player::checkCollision(class Asteroid *asteroidLayer[][8])
{
	for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
		for (int j = 0; j < ASTEROID_ARRAY_COLS; j++) {
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
