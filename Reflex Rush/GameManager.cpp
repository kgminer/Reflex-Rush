#include "GameManager.h"

using namespace std;

GameManager::GameManager(const char* title, int xpos, int ypos, int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
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
	
	backgroundTexture = TextureManager::LoadTexture("assets/SpaceBackground.png", renderer);
	running = true;
	inGame = false;
	player = new Player(renderer, screenWidth, screenHeight);

	for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
		for (int j = 0; j < ASTEROID_ARRAY_COLS; j++) {
			asteroidLayer[i][j] = new Asteroid(renderer, screenWidth, screenHeight, j);
		}
	}

	ui = new UIManager(renderer);
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
			uiMouseResponse = ui->handleEvents(inGame, gameOver, mouseX, mouseY);
			switch (uiMouseResponse)
			{
				case REPLAY_PRESSED:
					gameOver = false;
					paused = false;
					score = 0;
					spawnRow = 0;
					activeRows = 0;
					spawnTimer = 0;
					timeToSpawnAsteroid = SPAWN_TIMER;
					level = 1;
					difficulty = 1;
					levelThreshold = STARTING_LEVEL_THRESHOLD;
					spawnThreshold = CHANCE_TO_SPAWN_ASTEROID;
					player->centerShip(screenWidth, screenHeight);
					for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
						clearAsteroids(i);
					}
					spawnAsteroids(spawnRow % ASTEROID_ARRAY_ROWS);
					spawnRow++;
					activeRows++;
					currTime = SDL_GetTicks() / CONVERT_MS_TO_SEC;
					break;
				case RETURN_PRESSED:
					inGame = false;
					gameOver = false;
					player->centerShip(screenWidth, screenHeight);
					for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
						clearAsteroids(i);
					}
					Mix_PlayMusic(menuMusic, -1);
					break;
				case PLAY_PRESSED:
					inGame = true;
					gameOver = false;
					paused = false;
					score = 0;
					spawnRow = 0;
					activeRows = 0;
					spawnTimer = 0;
					timeToSpawnAsteroid = SPAWN_TIMER;
					level = 1;
					difficulty = 1;
					levelThreshold = STARTING_LEVEL_THRESHOLD;
					spawnThreshold = CHANCE_TO_SPAWN_ASTEROID;
					Mix_FadeOutMusic(1000);
					spawnAsteroids(spawnRow % ASTEROID_ARRAY_ROWS);
					spawnRow++;
					activeRows++;
					currTime = SDL_GetTicks() / CONVERT_MS_TO_SEC;
					break;
				default:
					break;
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
		if (!waitToSpawn) {
			score += level;
		}

		if (score > levelThreshold) {
			level++;
			if (level % 4 == 0) {
				difficulty = 2;
				spawnThreshold = CHANCE_TO_SPAWN_ASTEROID;
				timeToSpawnAsteroid = max(timeToSpawnAsteroid - SPAWN_TIMER_ADJUSTMENT, .5);
				waitToSpawn = true;
			}
			levelThreshold *= 2;
			spawnThreshold += SPAWN_THRESHOLD_ADJUSTMENT;
		}

		if (waitToSpawn) {
			if (spawnTimer > 3) {
				waitToSpawn = false;
			}
		}
		else if (spawnTimer > timeToSpawnAsteroid && activeRows < ASTEROID_ARRAY_ROWS) {
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
		ui->update(gameOver, renderer, score, level);
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
					asteroidLayer[i][j]->Render(renderer);
				}
			}
			
		}
		ui->RenderGame(gameOver, paused, renderer);
	}
	else {
		ui->RenderMenu(renderer);
	}

	SDL_RenderPresent(renderer);
}

void GameManager::clean()
{
	ui->~UIManager();
	player->~Player();
	for (int i = 0; i < ASTEROID_ARRAY_ROWS; i++) {
		for (int j = 0; j < ASTEROID_ARRAY_COLS; j++) {
			asteroidLayer[i][j]->~Asteroid();
		}
	}
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyRenderer(renderer);
	Mix_FreeMusic(menuMusic);
	Mix_Quit();
	SDL_Quit();
	TTF_Quit();
}

void GameManager::spawnAsteroids(int rowID)
{
	for (int i = 0; i < ASTEROID_ARRAY_COLS; i++) {
		randomNumber = (rand() % 100) + 1;
		if (randomNumber <= spawnThreshold) {
			asteroidLayer[rowID][i]->activateAsteroid(difficulty);
		}
	}
}

void GameManager::clearAsteroids(int rowID)
{
	for (int i = 0; i < ASTEROID_ARRAY_COLS; i++) {
		asteroidLayer[rowID][i]->deactivateAsteroid();
	}
}

bool GameManager::isRunning()
{
	return running;
}
