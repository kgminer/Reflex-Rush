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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
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
	spawnThreshold = 30;
	player = new Player(renderer, screenWidth, screenHeight);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++) {
			asteroidLayer[i][j] = new Asteroid(renderer, screenWidth, screenHeight, j);
		}
	}

	titleLabel = new Label("Reflex Rush", "assets/PSD/SHOWG.TTF", 64, white, 500, 300, renderer);
	
	gameOverLabel = new Label("Game Over", "assets/PSD/SHOWG.TTF", 64, white, 500, 300, renderer);
	
	pauseLabel = new Label("Paused", "assets/PSD/SHOWG.TTF", 100, white, 500, 0, renderer);
	unpauseTooltipLabel = new Label("Press ESC to unpause", "assets/PSD/SHOWG.TTF", 32, white, 510, 100, renderer);

	ss << "Score: " << score;
	scoreLabel = new Label(ss.str(), "assets/PSD/SHOWG.TTF", 25, white, 0, 0, renderer);
	finalScoreLabel = new Label("", "assets/PSD/SHOWG.TTF", 40, white, 500, 380, renderer);

	playLabel = new Label("Play", "assets/PSD/SHOWG.TTF", 40, white, 590, 480, renderer);
	playButton = new Button("assets/PNG/Buttons/BTNs/Play_BTN.png", "assets/PNG/Buttons/BTNs_Active/Play_BTN.png", 700, 450, 100, 100, renderer);
	
	replayLabel = new Label("Replay", "assets/PSD/SHOWG.TTF", 40, white, 580, 580, renderer);
	replayButton = new Button("assets/PNG/Buttons/BTNs/Replay_BTN.png", "assets/PNG/Buttons/BTNs_Active/Replay_BTN.png", 750, 550, 100, 100, renderer);

	returnToMenuLabel = new Label("Return To Menu", "assets/PSD/SHOWG.TTF", 40, white, 400, 480, renderer);
	returnToMenuButton = new Button("assets/PNG/Buttons/BTNs/Menu_BTN.png", "assets/PNG/Buttons/BTNs_Active/Menu_BTN.png", 750, 450, 100, 100, renderer);
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
					levelThreshold = 6000;
					player->centerShip(screenWidth, screenHeight);
					for (int i = 0; i < 5; i++) {
						clearAsteroids(i);
					}
					spawnAsteroids(spawnRow % 5);
					spawnRow++;
					activeRows++;
					currTime = SDL_GetTicks() / 1000.0;
				}
				else if ((mouseX > returnToMenuButton->getBoundsX()) && (mouseX < returnToMenuButton->getBoundsX() + returnToMenuButton->getBoundsW()) && (mouseY > returnToMenuButton->getBoundsY()) && (mouseY < returnToMenuButton->getBoundsY() + returnToMenuButton->getBoundsH())) {
					inGame = false;
					gameOver = false;
					player->centerShip(screenWidth, screenHeight);
					for (int i = 0; i < 5; i++) {
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
					levelThreshold = 6000;
					Mix_FadeOutMusic(1000);
					spawnAsteroids(spawnRow % 5);
					spawnRow++;
					activeRows++;
					currTime = SDL_GetTicks() / 1000.0;
				}
			}
			break;
		case SDL_KEYDOWN:
			if (inGame && !gameOver) {
				switch (event.key.keysym.sym)
				{
					case SDLK_LEFT:
					case SDLK_a:
						player->setXVelocity(-2);
						break;
					case SDLK_RIGHT:
					case SDLK_d:
						player->setXVelocity(2);
						break;
					case SDLK_UP:
					case SDLK_w:
						player->setYVelocity(-2);
						break;
					case SDLK_DOWN:
					case SDLK_s:
						player->setYVelocity(2);
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
			else {
				switch (event.key.keysym.sym)
				{
					case SDLK_p:
						//player->print();
						cout << playButton->getBoundsX() << " " << playButton->getBoundsY() << " " << playButton->getBoundsW() << " " << playButton->getBoundsH() << "\n";
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
	currTime = SDL_GetTicks() / 1000.0;
	deltaTime = currTime - prevTime;
	spawnTimer += deltaTime;

	if (!paused) {
		score = score + (1 * level);

		if (score > levelThreshold) {
			level++;
			cout << "Level " << level << "\n";
			levelThreshold = levelThreshold + (levelThreshold * level);
		}

		if (spawnTimer > SPAWN_TIMER && activeRows < 5) {
			spawnTimer = 0;
			spawnAsteroids(spawnRow % 5);
			spawnRow++;
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 8; j++) {
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

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 8; j++) {
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
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 8; j++) {
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
	for (int i = 0; i < 8; i++) {
		randomNumber = (rand() % 100) + 1;
		if (randomNumber <= spawnThreshold) {
			//cout << "Activating asteroid" << rowID << " " << i << " " << asteroidLayer[rowID][i]->getYMin() <<"\n";
			asteroidLayer[rowID][i]->activateAsteroid(level);
		}
	}
}

void GameManager::clearAsteroids(int rowID)
{
	for (int i = 0; i < 8; i++) {
		asteroidLayer[rowID][i]->deactivateAsteroid();
		//cout << "Deactivating asteroid" << rowID << " " << i <<  " " << asteroidLayer[rowID][i]->getYMin() << "\n";
	}
}

bool GameManager::isRunning()
{
	return running;
}
