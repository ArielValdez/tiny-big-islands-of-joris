#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Objects/TileMap.hpp"

GameObject* Player;
TileMap* map;
Vector2 Gravity;

SDL_Renderer* Game::Renderer = nullptr;

Game::Game()
{
	Window = nullptr;
	Player = nullptr;
	IsRunning = false;
	Disposed = false;
}

bool Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		printf("Could not init SDL");
		return false;
	}

	WindowRuleManager = new WindowManager();

	int windowFlag = 0;

	if (fullscreen) {
		windowFlag = SDL_WINDOW_FULLSCREEN;
	}
	else {
		windowFlag = SDL_WINDOW_RESIZABLE;
	}

	WindowRuleManager->Width = width;
	WindowRuleManager->Height = height;

	Game::Window = SDL_CreateWindow(title, xPos, yPos, WindowRuleManager->Width, WindowRuleManager->Height, windowFlag);
	if (Game::Window == nullptr)
	{
		std::printf("Error creating a new Window");
		return false;
	}

	Renderer = SDL_CreateRenderer(Game::Window, -1, SDL_RENDERER_ACCELERATED);
	if (Renderer == nullptr)
	{
		std::printf("Error creating a new Renderer");
		return false;
	}

	Player = new GameObject("Assets/Alma.png", 0, 0);
	map = new TileMap();

	Gravity = Vector2(0, 9.8); // Earth gravity
	IsRunning = true;
	return true;
}

void Game::Ready() {
	
}

void Game::Update(float delta) {
	Player->Update(delta);
}

void Game::PhysicsUpdate(float delta) {

}

void Game::HandleEvents() {
	SDL_Event sdlEvent;

	if (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			IsRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::Render() {
	SDL_RenderClear(Renderer);
	map->DrawMap();
	Player->Render();
	SDL_RenderPresent(Renderer);
}

void Game::Finalize() {
	// Destroy objects
	if (!Disposed) {
		SDL_DestroyWindow(Window);
		SDL_DestroyRenderer(Renderer);
		SDL_Quit();

		// Null pointers on pointers
		WindowRuleManager = nullptr;
		Window = nullptr;
		Renderer = nullptr;

		Disposed = true;
	}
}

Game::~Game() {
	Game::Finalize();
}