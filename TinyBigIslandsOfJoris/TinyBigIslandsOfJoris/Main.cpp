#include "src/Game.hpp"

Game* game = nullptr;

bool init() {
	game = new Game();

	return game->Init("Tiny Big Islands of Joris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
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

	game->Ready();

	while (game->Running())
	{
		game->HandleEvents();
		game->Update(0.0);
		game->PhysicsUpdate(0.0);
		game->Render();
	}

	return finalize();
}