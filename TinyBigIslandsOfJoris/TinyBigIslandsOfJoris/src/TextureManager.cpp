#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
	SDL_Surface* surface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::Renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect) {
	Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::Renderer, texture, &srcRect, &dstRect, NULL, NULL, flip);
}