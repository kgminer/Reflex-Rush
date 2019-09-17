#include "Label.h"

Label::Label(string labelText, string fp, int size, SDL_Color color, int x, int y, SDL_Renderer * ren)
{
	fontPath = fp;
	fontSize = size;
	textColor = color;
	position.x = x;
	position.y = y;
	setText(labelText, ren);
}

void Label::Render(SDL_Renderer * ren)
{
	SDL_RenderCopy(ren, labelTexture, nullptr, &position);
}

void Label::setText(string newText, SDL_Renderer * ren)
{
	SDL_Texture* oldTexture = labelTexture;
	SDL_DestroyTexture(oldTexture);
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	SDL_Surface* surface = TTF_RenderText_Blended(font, newText.c_str(), textColor);
	labelTexture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
}


Label::~Label()
{

}
