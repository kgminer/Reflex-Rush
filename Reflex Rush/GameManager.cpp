#include "GameManager.h"

using namespace std;

GameManager::GameManager(const char* title, int xpos, int ypos, int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	//Constants::init();
	srand(time(nullptr));

	if (TTF_Init() == -1) {
		cout << "Error initializing TTF\n";
	}

	if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNKSIZE) < 0) {
		cout << "Error initializeing Mixer\n";
	}
	menuMusic = Mix_LoadMUS("assets/Space Music Pack/menu.wav");
	Mix_PlayMusic(menuMusic, -1);
	screenWidth = width;
	screenHeight = height;
	window = SDL_CreateWindow(title , xpos, ypos, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Color white = { 255, 255, 255, 255};
	
	backgroundTexture = TextureManager::LoadTexture("assets/SpaceBackground.png", renderer);
	running = true;
	inGame = false;
	spawnThreshold = CHANCE_TO_SPAWN_ASTEROID;
	player = new Player(renderer, screenWidth, screenHeight);

	for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
		for (int j = 0; j < ASTEROID_ARRAY_COLS; j++) {
			asteroidLayer[i][j] = new Asteroid(renderer, screenWidth, screenHeight, j);
		}
	}

	titleLabel = new Label("Reflex Rush", "assets/PSD/SHOWG.TTF", TITLE_LABEL_SIZE, white, TITLE_LABEL_X, TITLE_LABEL_Y, renderer);
	
	gameOverLabel = new Label("Game Over", "assets/PSD/SHOWG.TTF", GAME_OVER_LABEL_SIZE, white, GAME_OVER_LABEL_X, GAME_OVER_LABEL_Y, renderer);
	
	pauseLabel = new Label("Paused", "assets/PSD/SHOWG.TTF", PAUSE_LABEL_SIZE, white, PAUSE_LABEL_X, PAUSE_LABEL_Y, renderer);
	unpauseTooltipLabel = new Label("Press ESC to unpause", "assets/PSD/SHOWG.TTF", UNPAUSE_TIP_LABEL_SIZE, white, UNPAUSE_TIP_LABEL_X, UNPAUSE_TIP_LABEL_Y, renderer);

	ss << "Score: " << score;
	scoreLabel = new Label(ss.str(), "assets/PSD/SHOWG.TTF", SCORE_LABEL_SIZE, white, SCORE_LABEL_X, SCORE_LABEL_Y, renderer);
	finalScoreLabel = new Label("", "assets/PSD/SHOWG.TTF", FINAL_SCORE_LABEL_SIZE, white, FINAL_SCORE_LABEL_X, FINAL_SCORE_LABEL_Y, renderer);

	playLabel = new Label("Play", "assets/PSD/SHOWG.TTF", PLAY_LABEL_SIZE, white, PLAY_LABEL_X, PLAY_LABEL_Y, renderer);
	playButton = new Button("assets/PNG/Buttons/BTNs/Play_BTN.png", "assets/PNG/Buttons/BTNs_Active/Play_BTN.png", PLAY_BUTTON_X, PLAY_BUTTON_Y, PLAY_BUTTON_W, PLAY_BUTTON_H, renderer);
	
	replayLabel = new Label("Replay", "assets/PSD/SHOWG.TTF", REPLAY_LABEL_SIZE, white, REPLAY_LABEL_X, REPLAY_LABEL_Y, renderer);
	replayButton = new Button("assets/PNG/Buttons/BTNs/Replay_BTN.png", "assets/PNG/Buttons/BTNs_Active/Replay_BTN.png", REPLAY_BUTTON_X, REPLAY_BUTTON_Y, REPLAY_BUTTON_W, REPLAY_BUTTON_H, renderer);

	returnToMenuLabel = new Label("Return To Menu", "assets/PSD/SHOWG.TTF", RETURN_TO_MENU_LABEL_SIZE, white, RETURN_TO_MENU_LABEL_X, RETURN_TO_MENU_LABEL_Y, renderer);
	returnToMenuButton = new Button("assets/PNG/Buttons/BTNs/Menu_BTN.png", "assets/PNG/Buttons/BTNs_Active/Menu_BTN.png", RETURN_TO_MENU_BUTTON_X, RETURN_TO_MENU_BUTTON_Y, RETURN_TO_MENU_BUTTON_W, RETURN_TO_MENU_BUTTON_H, renderer);
}


GameManager::~GameManager()
{
}

void GameManager::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			if (inGame && gameOver) {
				if ((mouseX > replayButton->getBoundsX()) && (mouseX < replayButton->getBoundsX() + replayButton->getBoundsW()) && (mouseY > replayButton->getBoundsY()) && (mouseY < replayButton->getBoundsY() + replayButton->getBoundsH())) {
					gameOver = false;
					paused = false;
					score = 0;
					spawnRow = 0;
					activeRows = 0;
					level = 1;
					levelThreshold = STARTING_LEVEL_THRESHOLD;
					player->centerShip(screenWidth, screenHeight);
					for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
						clearAsteroids(i);
					}
					spawnAsteroids(spawnRow % ASTEROID_ARRAY_ROWS);
					spawnRow++;
					activeRows++;
					currTime = SDL_GetTicks() / CONVERT_MS_TO_SEC;
				}
				else if ((mouseX > returnToMenuButton->getBoundsX()) && (mouseX < returnToMenuButton->getBoundsX() + returnToMenuButton->getBoundsW()) && (mouseY > returnToMenuButton->getBoundsY()) && (mouseY < returnToMenuButton->getBoundsY() + returnToMenuButton->getBoundsH())) {
					inGame = false;
					gameOver = false;
					player->centerShip(screenWidth, screenHeight);
					for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
						clearAsteroids(i);
					}
					Mix_PlayMusic(menuMusic, -1);
				}
			}
			else if(!inGame) {
				//cout << "x: " << mouseX << " y: " << mouseY << "\n";
				if ((mouseX > playButton->getBoundsX()) && (mouseX < playButton->getBoundsX() + playButton->getBoundsW()) && (mouseY > playButton->getBoundsY()) && (mouseY < playButton->getBoundsY() + playButton->getBoundsH())) {
					inGame = true;
					gameOver = false;
					paused = false;
					score = 0;
					spawnRow = 0;
					activeRows = 0;
					level = 1;
					levelThreshold = STARTING_LEVEL_THRESHOLD;
					Mix_FadeOutMusic(1000);
					spawnAsteroids(spawnRow % ASTEROID_ARRAY_ROWS);
					spawnRow++;
					activeRows++;
					currTime = SDL_GetTicks() / CONVERT_MS_TO_SEC;
				}
			}
			break;
		case SDL_KEYDOWN:
			if (inGame && !gameOver) {
				switch (event.key.keysym.sym)
				{
					case SDLK_LEFT:
					case SDLK_a:
						player->setXVelocity(-PLAYER_MOVEMENT_VELOCITY);
						break;
					case SDLK_RIGHT:
					case SDLK_d:
						player->setXVelocity(PLAYER_MOVEMENT_VELOCITY);
						break;
					case SDLK_UP:
					case SDLK_w:
						player->setYVelocity(-PLAYER_MOVEMENT_VELOCITY);
						break;
					case SDLK_DOWN:
					case SDLK_s:
						player->setYVelocity(PLAYER_MOVEMENT_VELOCITY);
						break;
					default:
						break;
				}
			}
			break;
		case SDL_KEYUP:
			if (inGame && !gameOver) {
				switch (event.key.keysym.sym)
				{
					case SDLK_LEFT:
					case SDLK_a:
						player->setXVelocity(0);
						break;
					case SDLK_RIGHT:
					case SDLK_d:
						player->setXVelocity(0);
						break;
					case SDLK_UP:
					case SDLK_w:
						player->setYVelocity(0);
						break;
					case SDLK_DOWN:
					case SDLK_s:
						player->setYVelocity(0);
						break;
					case SDLK_p:
						player->print();
						break;
					case SDLK_ESCAPE:
						if (paused) {
							paused = false;
						}
						else {
							paused = true;
							player->setXVelocity(0);
							player->setYVelocity(0);
						}
						break;
					default:
						break;
				}
			}
			break;
	}
}

void GameManager::update()
{
	if (gameOver || !inGame) {
		return;
	}
	prevTime = currTime;
	currTime = SDL_GetTicks() / CONVERT_MS_TO_SEC;
	deltaTime = currTime - prevTime;
	spawnTimer += deltaTime;

	if (!paused) {
		score = score + level;

		if (score > levelThreshold) {
			level++;
			cout << "Level " << level << "\n";
			levelThreshold = levelThreshold + (levelThreshold * level);
		}

		if (spawnTimer > SPAWN_TIMER && activeRows < ASTEROID_ARRAY_ROWS) {
			spawnTimer = 0;
			spawnAsteroids(spawnRow % ASTEROID_ARRAY_ROWS);
			spawnRow++;
		}
		for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
			for (int j = 0; j < ASTEROID_ARRAY_COLS; j++) {
				if (asteroidLayer[i][j]->getActive() == true) {
					asteroidLayer[i][j]->Update();
				}
			}
		}
		gameOver = player->Update(screenWidth, screenHeight, asteroidLayer);
		if (gameOver) {
			ss.str("");
			ss << "Final Score: " << score;
			finalScoreLabel->setText(ss.str(), renderer);
			ss.str("");
			ss << "Score: " << score;
			scoreLabel->setText(ss.str(), renderer);
		}
		else {
			ss.str("");
			ss << "Score: " << score;
			scoreLabel->setText(ss.str(), renderer);
		}

		for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
			for (int j = 0; j < ASTEROID_ARRAY_COLS; j++) {
				if (asteroidLayer[i][j]->getActive() == true) {
					if (asteroidLayer[i][j]->getYMin() > screenHeight) {
						clearAsteroids(i);
						activeRows--;
					}
					break;
				}
			}
			
		}
	}
}

void GameManager::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	if (inGame) {
		player->Render(renderer);
		for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
			for (int j = 0; j < ASTEROID_ARRAY_COLS; j++) {
				if (asteroidLayer[i][j]->getActive() == true) {
					//cout << "Rendering: " << i << " " << j << "\n";
					asteroidLayer[i][j]->Render(renderer);
				}
			}
			
		}
		scoreLabel->Render(renderer);
		if (gameOver) {
			
			gameOverLabel->Render(renderer);
			finalScoreLabel->Render(renderer);
			returnToMenuLabel->Render(renderer);
			returnToMenuButton->Render(renderer);
			replayLabel->Render(renderer);
			replayButton->Render(renderer);
		}
		if (paused) {
			pauseLabel->Render(renderer);
			unpauseTooltipLabel->Render(renderer);
		}
	}
	else {

		titleLabel->Render(renderer);
		playLabel->Render(renderer);
		playButton->Render(renderer);
	}

	SDL_RenderPresent(renderer);
}

void GameManager::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_FreeMusic(menuMusic);
	Mix_Quit();
	SDL_Quit();
	TTF_Quit();
}

void GameManager::spawnAsteroids(int rowID)
{
	//cout << "Spawning row" << rowID << "\n";
	for (int i = 0; i < ASTEROID_ARRAY_COLS; i++) {
		randomNumber = (rand() % 100) + 1;
		if (randomNumber <= spawnThreshold) {
			//cout << "Activating asteroid" << rowID << " " << i << " " << asteroidLayer[rowID][i]->getYMin() <<"\n";
			asteroidLayer[rowID][i]->activateAsteroid(level);
		}
	}
}

void GameManager::clearAsteroids(int rowID)
{
	for (int i = 0; i < ASTEROID_ARRAY_COLS; i++) {
		asteroidLayer[rowID][i]->deactivateAsteroid();
		//cout << "Deactivating asteroid" << rowID << " " << i <<  " " << asteroidLayer[rowID][i]->getYMin() << "\n";
	}
}

bool GameManager::isRunning()
{
	return running;
}
