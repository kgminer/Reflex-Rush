#include "UIManager.h"

using namespace std;

UIManager::UIManager(SDL_Renderer *ren)
{
	SDL_Color white = { 255, 255, 255, 255 };

	titleLabel = new Label("Reflex Rush", "assets/PSD/SHOWG.TTF", TITLE_LABEL_SIZE, white, TITLE_LABEL_X, TITLE_LABEL_Y, ren);

	gameOverLabel = new Label("Game Over", "assets/PSD/SHOWG.TTF", GAME_OVER_LABEL_SIZE, white, GAME_OVER_LABEL_X, GAME_OVER_LABEL_Y, ren);

	pauseLabel = new Label("Paused", "assets/PSD/SHOWG.TTF", PAUSE_LABEL_SIZE, white, PAUSE_LABEL_X, PAUSE_LABEL_Y, ren);
	unpauseTooltipLabel = new Label("Press ESC to unpause", "assets/PSD/SHOWG.TTF", UNPAUSE_TIP_LABEL_SIZE, white, UNPAUSE_TIP_LABEL_X, UNPAUSE_TIP_LABEL_Y, ren);

	ss << "Score: " << 0;
	scoreLabel = new Label(ss.str(), "assets/PSD/SHOWG.TTF", SCORE_LABEL_SIZE, white, SCORE_LABEL_X, SCORE_LABEL_Y, ren);
	finalScoreLabel = new Label("", "assets/PSD/SHOWG.TTF", FINAL_SCORE_LABEL_SIZE, white, FINAL_SCORE_LABEL_X, FINAL_SCORE_LABEL_Y, ren);

	playLabel = new Label("Play", "assets/PSD/SHOWG.TTF", PLAY_LABEL_SIZE, white, PLAY_LABEL_X, PLAY_LABEL_Y, ren);
	playButton = new Button("assets/PNG/Buttons/BTNs/Play_BTN.png", "assets/PNG/Buttons/BTNs_Active/Play_BTN.png", PLAY_BUTTON_X, PLAY_BUTTON_Y, PLAY_BUTTON_W, PLAY_BUTTON_H, ren);

	replayLabel = new Label("Replay", "assets/PSD/SHOWG.TTF", REPLAY_LABEL_SIZE, white, REPLAY_LABEL_X, REPLAY_LABEL_Y, ren);
	replayButton = new Button("assets/PNG/Buttons/BTNs/Replay_BTN.png", "assets/PNG/Buttons/BTNs_Active/Replay_BTN.png", REPLAY_BUTTON_X, REPLAY_BUTTON_Y, REPLAY_BUTTON_W, REPLAY_BUTTON_H, ren);

	returnToMenuLabel = new Label("Return To Menu", "assets/PSD/SHOWG.TTF", RETURN_TO_MENU_LABEL_SIZE, white, RETURN_TO_MENU_LABEL_X, RETURN_TO_MENU_LABEL_Y, ren);
	returnToMenuButton = new Button("assets/PNG/Buttons/BTNs/Menu_BTN.png", "assets/PNG/Buttons/BTNs_Active/Menu_BTN.png", RETURN_TO_MENU_BUTTON_X, RETURN_TO_MENU_BUTTON_Y, RETURN_TO_MENU_BUTTON_W, RETURN_TO_MENU_BUTTON_H, ren);
}

int UIManager::handleEvents(bool inGame, bool gameOver, int mouseX, int mouseY)
{
	if (inGame && gameOver) {
		if ((mouseX > replayButton->getBoundsX()) && (mouseX < replayButton->getBoundsX() + replayButton->getBoundsW()) && (mouseY > replayButton->getBoundsY()) && (mouseY < replayButton->getBoundsY() + replayButton->getBoundsH())) {
			return 1;
		}
		else if ((mouseX > returnToMenuButton->getBoundsX()) && (mouseX < returnToMenuButton->getBoundsX() + returnToMenuButton->getBoundsW()) && (mouseY > returnToMenuButton->getBoundsY()) && (mouseY < returnToMenuButton->getBoundsY() + returnToMenuButton->getBoundsH())) {
			return 2;
		}
	}
	else if (!inGame) {
		//cout << "x: " << mouseX << " y: " << mouseY << "\n";
		if ((mouseX > playButton->getBoundsX()) && (mouseX < playButton->getBoundsX() + playButton->getBoundsW()) && (mouseY > playButton->getBoundsY()) && (mouseY < playButton->getBoundsY() + playButton->getBoundsH())) {
			return 3;
		}
	}
	return 0;
}

void UIManager::update(bool gameOver, SDL_Renderer *ren, int score)
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
