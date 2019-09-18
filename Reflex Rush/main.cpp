#include "GameManager.h"

int main(int argc, char *argv[]) {

	GameManager *manager = new GameManager("Reflex Rush", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 900);

	while (manager->isRunning()) {
		manager->handleEvents();
		manager->update();
		manager->render();
	}

	manager->clean();
	
	return 0;
}