#include "Button.h"

Button::Button(string filePath, int x, int y, int w, int h, SDL_Renderer* ren)
{
	buttonImage = TextureManager::LoadTexture(filePath.c_str(), ren);
	buttonBounds.x = x;
	buttonBounds.y = y;
	buttonBounds.w = w;
	buttonBounds.h = h;
}

void Button::Render(SDL_Renderer * ren)
{
	SDL_RenderCopy(ren, buttonImage, nullptr, &buttonBounds);
}

int Button::getBoundsX()
{
	return buttonBounds.x;
}

int Button::getBoundsY()
{
	return buttonBounds.y;
}

int Button::getBoundsW()
{
	return buttonBounds.w;
}

int Button::getBoundsH()
{
	return buttonBounds.h;
}


Button::~Button()
{
	SDL_DestroyTexture(buttonImage);
}
