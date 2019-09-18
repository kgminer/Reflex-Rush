#include "TextureManager.h"

using namespace std;

SDL_Texture * TextureManager::LoadTexture(const char * fileName, SDL_Renderer * ren)
{
	cout << fileName << "\n";
	SDL_Surface *tempSuface = IMG_Load(fileName);
	SDL_Texture*  texture = SDL_CreateTextureFromSurface(ren, tempSuface);
	SDL_FreeSurface(tempSuface);
	return texture;
}
