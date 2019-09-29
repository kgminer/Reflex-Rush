#include "Label.h"

Label::Label(string labelText, string fp, int size, SDL_Color color, int x, int y, SDL_Renderer * ren)
{
	fontPath = fp;
	fontSize = size;
	textColor = color;
	position.x = x;
	position.y = y;
	font = TTF_OpenFont(fontPath.c_str(), fontSize);
	setText(labelText, ren);
}

void Label::Render(SDL_Renderer * ren)
{
	SDL_RenderCopy(ren, labelTexture, nullptr, &position);
}

void Label::setText(string newText, SDL_Renderer * ren)
{
	SDL_Surface* surface = TTF_RenderText_Blended(font, newText.c_str(), textColor);
	if (labelTexture != nullptr) {
		SDL_DestroyTexture(labelTexture);
	}
	labelTexture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	SDL_FreeSurface(surface);
}


Label::~Label()
{
	TTF_CloseFont(font);
}
