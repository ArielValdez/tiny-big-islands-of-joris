#include "Game.hpp"
#include "TextureManager.hpp"
#include "Objects/TileMap.hpp"
#include "Objects/ECS/Entities.hpp"
#include "Objects/ECS/Components.hpp"

TileMap* map;
Vector2 Gravity;

Manager manager;

SDL_Renderer* Game::Renderer = nullptr;
std::vector<Collider*> Game::Colliders;

Player& player = (Player&)(manager.AddEntity<Player>());
Entity& wall = manager.AddEntity();
Entity& tile0 = manager.AddEntity();

Game::Game()
{
	Window = nullptr;
	IsRunning = false;
	Disposed = false;
}

bool Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		printf("Could not init SDL");
		return false;
	}

	Gravity = Vector2(0, 9.8); // Earth gravity

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

	player.AddComponent<Collider>(
		Vector2(32, 32), 
		CollissionMapLayer::PLAYER, 
		CollissionMapLayer::ENEMY | CollissionMapLayer::WORLD_DEFAULT | CollissionMapLayer::ENEMY_PROJECTILE | CollissionMapLayer::TRAP);
	player.AddComponent<Sprite>("Assets/Alma.png", Vector2(32, 32));
	player.AddComponent<Controller>();

	wall.AddComponent<Collider>(
		Vector2(32, 32),
		CollissionMapLayer::WORLD_DEFAULT,
		CollissionMapLayer::ENEMY | CollissionMapLayer::PLAYER | CollissionMapLayer::ENEMY_PROJECTILE | CollissionMapLayer::PLAYER_PROJECTILE);
	wall.AddComponent<Sprite>("Assets/dirt.jpg", Vector2(32, 32));
	wall.Position = Vector2(128, 128);

	tile0.AddComponent<Tile>(0, 0, 32, 32, 1);
	tile0.Position = Vector2(256, 256);

	map = new TileMap();

	manager.Init();

	IsRunning = true;
	return true;
}

void Game::Ready() {

}

void Game::Update(double delta) {
	//Player->Update(delta);
	manager.Refresh();
	manager.Update(delta);

	if (Collission::AABB(&player.GetComponent<Collider>(), &wall.GetComponent<Collider>()))
	{
		std::cout << "Lol ex di even" << std::endl;
		player.Velocity = player.Velocity * -1;
	}
}

void Game::PhysicsUpdate(double delta) {
	manager.PhysicsUpdate(delta);
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

	manager.HandleEvents(sdlEvent);
}

void Game::Render() {
	SDL_RenderClear(Renderer);
	map->DrawMap();
	manager.Draw();
	SDL_RenderPresent(Renderer);
}

void Game::Finalize() {
	// Destroy objects
	if (!Disposed) {
		SDL_DestroyWindow(Window);
		SDL_DestroyRenderer(Renderer);
		SDL_Quit();

		// Null pointers on pointers
		manager.Destroy();
		WindowRuleManager = nullptr;
		Window = nullptr;
		Renderer = nullptr;
		Disposed = true;
	}
}

Game::~Game() {
	Game::Finalize();
}