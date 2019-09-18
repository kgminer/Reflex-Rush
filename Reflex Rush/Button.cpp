#include "Button.h"

Button::Button(string inactivefilePath, string activefilePath, int x, int y, int w, int h, SDL_Renderer* ren)
{
	inactiveButtonImage = TextureManager::LoadTexture(inactivefilePath.c_str(), ren);
	activeButtonImage = TextureManager::LoadTexture(activefilePath.c_str(), ren);
	buttonBounds.x = x;
	buttonBounds.y = y;
	buttonBounds.w = w;
	buttonBounds.h = h;
	activeStatus = false;
}

void Button::Render(SDL_Renderer * ren)
{
	if (!activeStatus) {
		SDL_RenderCopy(ren, inactiveButtonImage, nullptr, &buttonBounds);
	}
	else {
		SDL_RenderCopy(ren, activeButtonImage, nullptr, &buttonBounds);
	}
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

}
