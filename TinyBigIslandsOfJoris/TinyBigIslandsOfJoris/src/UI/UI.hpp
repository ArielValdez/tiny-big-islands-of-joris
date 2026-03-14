#pragma once
#include <SDL.h>
#include <SDL_image.h>

SDL_Color WHITE = { 255, 255, 255 };
SDL_Color RED = { 255, 0, 0 };
SDL_Color GREEN = { 0, 255, 0 };
SDL_Color BLUE = { 0, 0, 255 };
SDL_Color BLACK = { 0, 0, 0 };

class UI {
	virtual void Draw(SDL_Rect camera) {

	}

};