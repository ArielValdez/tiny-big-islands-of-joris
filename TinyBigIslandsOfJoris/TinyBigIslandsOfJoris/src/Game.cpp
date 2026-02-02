#include "Game.hpp"
#include "TextureManager.hpp"

SDL_Texture* playerTexture;
SDL_Rect destR;
SDL_Rect srcR;

Game::Game()
{
	Renderer = nullptr;
	Window = nullptr;
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

	playerTexture = TextureManager::LoadTexture("Assets/Alma.png", Renderer);

	if (playerTexture == nullptr)
	{
		std::printf("Error creating texture");
		return false;
	}

	IsRunning = true;
	return true;
}

void Game::Ready() {

}

void Game::Update(float delta) {
	printf("HELLO");

	destR.w = 64;
	destR.h = 64;
	destR.x += 1;
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
	else
	{
		printf("No pending events.");
	}
}

void Game::Render() {
	SDL_RenderClear(Renderer);
	SDL_RenderCopy(Renderer, playerTexture, nullptr, &destR);
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