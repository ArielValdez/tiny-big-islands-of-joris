#include "src/Game.hpp"

Game* game = nullptr;

bool init() {
	game = new Game();

	return game->Init("Tiny Big Islands of Joris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
}

int finalize() {
	// Clean up everything here
	game->Finalize();

	game = nullptr;
	return 0;
}

int main(int argc, char* args[]) {
	bool running = true;

	if (!init())
	{
		return 903;
	}

	size_t frameStart;
	int frameTime;
	float deltaTime = (float)SDL_GetTicks();

	game->Ready();

	// TODO make game loop better
	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update(deltaTime);
		game->PhysicsUpdate(deltaTime);
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;
		deltaTime = game->WindowRuleManager->FrameDelay - frameTime;
		if (game->WindowRuleManager->FrameDelay > frameTime)
		{
			SDL_Delay(deltaTime);
		}
	}

	return finalize();
}