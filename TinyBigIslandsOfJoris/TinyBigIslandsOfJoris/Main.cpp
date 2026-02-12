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

void cleanup() {
	finalize();
}

int main(int argc, char* args[]) {
	bool running = true;

	if (!init())
	{
		return 903;
	}

	//std::atexit(cleanup);

	size_t frameStart;
	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	int frameTime;
	float delta = (float)SDL_GetTicks();
	double deltaTime = 0;

	game->Ready();

	while (game->Running())
	{
		last = now;
		now = SDL_GetPerformanceCounter();

		frameStart = SDL_GetTicks();

		deltaTime = (((now - last) * 1000.f / (double)SDL_GetPerformanceFrequency()) * game->WindowRuleManager->TargetFps);
		if (deltaTime >= game->WindowRuleManager->TargetDeltaTime)
		{
			deltaTime = game->WindowRuleManager->TargetDeltaTime;
		}

		//std::cout << deltaTime << std::endl;

		game->HandleEvents();
		game->Update(deltaTime);
		game->PhysicsUpdate(deltaTime);
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;
		delta = game->WindowRuleManager->FrameDelay - frameTime;
		if (game->WindowRuleManager->FrameDelay > frameTime)
		{
			SDL_Delay(delta);
		}
	}

	return finalize();
}