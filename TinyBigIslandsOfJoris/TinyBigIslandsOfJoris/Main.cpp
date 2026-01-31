#include <SDL.h>
#include <iostream>
#include "Main.h"
#include "src/Window.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Window* ruleWindow = NULL;

bool init() {
	bool result = true;
	ruleWindow = new Window();

	window = SDL_CreateWindow("Tiny Big Island of Joris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ruleWindow->Width, ruleWindow->Height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::printf("Error creating a new Window");
		result = false;
		return result;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::printf("Error creating a new Renderer");
		result = false;
		return result;
	}

	return result;
}

int finalize() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}

int main(int argc, char* args[]) {
	bool running = true;

	if (!init())
	{
		return 903;
	}

	while (running)
	{
		SDL_Event event;

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				break;
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

		SDL_Delay(ruleWindow->FPS);
	}

	return finalize();
}