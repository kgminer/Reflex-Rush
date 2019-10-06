#pragma once
#include "GameManager.h"
#include <string>

using namespace std;

class Button
{
public:
	Button(string filePath, int x, int y, int w, int h, SDL_Renderer* ren);
	void Render(SDL_Renderer* ren);
	int getBoundsX();
	int getBoundsY();
	int getBoundsW();
	int getBoundsH();
	~Button();
private:
	SDL_Texture *buttonImage;
	SDL_Rect buttonBounds;
};

