#pragma once
#include "SDL.H"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Player.h"
#include "TextureManager.h"
#include "Asteroid.h"
#include "Label.h"
#include "Button.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

class GameManager
{
public:
	GameManager(const char* title, int xpos, int ypos, int width, int height);
	~GameManager();

	void handleEvents();
	void update();
	void render();
	void clean();
	void spawnAsteroids(int rowID);
	void clearAsteroids(int rowID);
	bool isRunning();
private:

	bool running, inGame, gameOver, paused;
	int screenWidth, screenHeight, mouseX, mouseY, score, randomNumber, spawnThreshold, spawnRow, activeRows, level, levelThreshold;
	double currTime, prevTime, deltaTime, spawnTimer;
	stringstream ss;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *backgroundTexture;
	Mix_Music *menuMusic;
	class Player *player;
	class Asteroid *asteroidLayer[5][8];
	class Label *titleLabel, *playLabel, *replayLabel, *pauseLabel, *unpauseTooltipLabel, *scoreLabel, *finalScoreLabel, *returnToMenuLabel, *gameOverLabel;
	class Button *playButton, *replayButton, *returnToMenuButton;
};

