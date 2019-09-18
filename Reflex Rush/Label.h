#pragma once
#include "GameManager.h"
#include <string>

using namespace std;

class Label
{
public:
	Label(string labelText, string fp, int size, SDL_Color color, int x, int y, SDL_Renderer * ren);
	void Render(SDL_Renderer* ren);
	void setText(string newText, SDL_Renderer * ren);
	~Label();
private:
	SDL_Rect position;
	SDL_Texture* labelTexture;
	string fontPath;
	int fontSize;
	SDL_Color textColor;
};

