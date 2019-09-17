#pragma once
#include "GameManager.h"

class UIManager
{
public:
	UIManager(SDL_Renderer *ren);
	void update(bool gameOver, SDL_Renderer *ren);
	void RenderMenu(SDL_Renderer *ren);
	void RenderGame(bool gameOver, bool paused, SDL_Renderer *ren);
	~UIManager();
private:
	int score;
	stringstream ss;
	Mix_Music *menuMusic;
	class Label *titleLabel, *playLabel, *replayLabel, *pauseLabel, *unpauseTooltipLabel, *scoreLabel, *finalScoreLabel, *returnToMenuLabel, *gameOverLabel;
	class Button *playButton, *replayButton, *returnToMenuButton;
};

