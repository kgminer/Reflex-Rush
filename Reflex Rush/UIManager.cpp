#include "UIManager.h"



UIManager::UIManager(SDL_Renderer *ren)
{
	SDL_Color white = { 255, 255, 255, 255 };

	titleLabel = new Label("Reflex Rush", "assets/PSD/SHOWG.TTF", 64, white, 500, 300, ren);

	gameOverLabel = new Label("Game Over", "assets/PSD/SHOWG.TTF", 64, white, 500, 300, ren);

	pauseLabel = new Label("Paused", "assets/PSD/SHOWG.TTF", 100, white, 500, 0, ren);
	unpauseTooltipLabel = new Label("Press ESC to unpause", "assets/PSD/SHOWG.TTF", 32, white, 510, 100, ren);

	ss << "Score: " << score;
	scoreLabel = new Label(ss.str(), "assets/PSD/SHOWG.TTF", 25, white, 0, 0, ren);
	finalScoreLabel = new Label("", "assets/PSD/SHOWG.TTF", 40, white, 500, 380, ren);

	playLabel = new Label("Play", "assets/PSD/SHOWG.TTF", 40, white, 590, 480, ren);
	playButton = new Button("assets/PNG/Buttons/BTNs/Play_BTN.png", "assets/PNG/Buttons/BTNs_Active/Play_BTN.png", 700, 450, 100, 100, ren);

	replayLabel = new Label("Replay", "assets/PSD/SHOWG.TTF", 40, white, 580, 580, ren);
	replayButton = new Button("assets/PNG/Buttons/BTNs/Replay_BTN.png", "assets/PNG/Buttons/BTNs_Active/Replay_BTN.png", 750, 550, 100, 100, ren);

	returnToMenuLabel = new Label("Return To Menu", "assets/PSD/SHOWG.TTF", 40, white, 400, 480, ren);
	returnToMenuButton = new Button("assets/PNG/Buttons/BTNs/Menu_BTN.png", "assets/PNG/Buttons/BTNs_Active/Menu_BTN.png", 750, 450, 100, 100, ren);
}

void UIManager::update(bool gameOver, SDL_Renderer *ren)
{
	if (gameOver) {
		ss.str("");
		ss << "Final Score: " << score;
		finalScoreLabel->setText(ss.str(), ren);
		ss.str("");
		ss << "Score: " << score;
		scoreLabel->setText(ss.str(), ren);
	}
	else {
		ss.str("");
		ss << "Score: " << score;
		scoreLabel->setText(ss.str(), ren);
	}
}

void UIManager::RenderMenu(SDL_Renderer *ren)
{
	titleLabel->Render(ren);
	playLabel->Render(ren);
	playButton->Render(ren);
}

void UIManager::RenderGame(bool gameOver, bool paused, SDL_Renderer *ren)
{
	scoreLabel->Render(ren);
	if (gameOver) {

		gameOverLabel->Render(ren);
		finalScoreLabel->Render(ren);
		returnToMenuLabel->Render(ren);
		returnToMenuButton->Render(ren);
		replayLabel->Render(ren);
		replayButton->Render(ren);
	}
	if (paused) {
		pauseLabel->Render(ren);
		unpauseTooltipLabel->Render(ren);
	}
}


UIManager::~UIManager()
{

}
