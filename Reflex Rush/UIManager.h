#pragma once
#include "GameManager.h"
#include <sstream>

using namespace std;

class UIManager
{
public:
	UIManager(SDL_Renderer *ren);
	int handleEvents(bool inGame, bool gameOver, int mouseX, int mouseY);
	void update(bool gameOver, SDL_Renderer *ren, int score, int level);
	void RenderMenu(SDL_Renderer *ren);
	void RenderGame(bool gameOver, bool paused, SDL_Renderer *ren);
	~UIManager();
private:
	stringstream ss;
	class Label *titleLabel, *playLabel, *replayLabel, *pauseLabel, *unpauseTooltipLabel, *scoreLabel, *finalScoreLabel, *levelLabel, *returnToMenuLabel, *gameOverLabel;
	class Button *playButton, *replayButton, *returnToMenuButton;
};

