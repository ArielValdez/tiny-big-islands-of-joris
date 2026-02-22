#include "Game.hpp"
#include "TextureManager.hpp"
#include "Objects/TileMap.hpp"
#include "Objects/ECS/Entities.hpp"
#include "Objects/ECS/Components.hpp"
#include "Objects/Enums/GroupLabels.hpp"

TileMap* map;
Vector2 Gravity;

Manager manager;

#pragma region Static
SDL_Renderer* Game::Renderer = nullptr;
std::vector<Collider*> Game::Colliders;
bool Game::IsRunning = false;
SDL_Rect Game::Camera = { 0, 0, 500, 500 };
#pragma endregion

Player& player = (Player&)(manager.AddEntity<Player>());

const char* spriteSheetMap = "Assets/terrain_ss.png";

auto& players = manager.GetGroup(GroupLabels::PLAYERS);
auto& tiles = manager.GetGroup(GroupLabels::MAP);
auto& enemies = manager.GetGroup(GroupLabels::ENEMIES);

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
	Game::Camera = { 0, 0, WindowRuleManager->Width, WindowRuleManager->Height };
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

	map = new TileMap();
	map->LoadMap("Assets/map.map", 32, 32, 32, 32);

	player.AddComponent<Collider>(
		Vector2(32, 32),
		CollissionMapLayer::PLAYER,
		CollissionMapLayer::ENEMY | CollissionMapLayer::WORLD_DEFAULT | CollissionMapLayer::ENEMY_PROJECTILE | CollissionMapLayer::TRAP);
	player.AddComponent<Sprite>("Assets/Alma.png", Vector2(32, 32));
	player.AddComponent<KeyboardController>();
	player.AddGroup(GroupLabels::PLAYERS);

	manager.Init();

	IsRunning = true;
	return true;
}

void Game::Ready() {

}

void Game::Update(double delta) {
	manager.Refresh();
	manager.Update(delta);

	Camera.x = player.Position.X - (WindowRuleManager->Width / 2);
	Camera.y = player.Position.Y - (WindowRuleManager->Height / 2);
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
	//manager.Draw(); // Refactor

	for (auto& t : tiles)
	{
		t->Draw();
	}

	for (auto& t : players)
	{
		t->Draw();
	}

	for (auto& t : enemies)
	{
		t->Draw();
	}

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

void Game::AddTile(int id, int srcX, int srcY, int dstX, int dstY, int w, int h, const char* path) {
	auto& tile = manager.AddEntity();
	tile.AddComponent<Tile>(srcX, srcY, dstX, dstY, w, h, id, spriteSheetMap);
	tile.AddGroup(GroupLabels::MAP);
}

void Game::AddTile(int id, Vector2 atlas, Vector2 pos, const char* path) {
	AddTile(id, atlas.X, atlas.Y, pos.X, pos.Y, 32, 32, path);
}

void Game::AddTile(int id, Vector2 atlas, Vector2 pos, Vector2 size, const char* path) {
	AddTile(id, atlas.X, atlas.Y, pos.X, pos.Y, size.X, size.Y, path);
}

float Game::MoveTowards(float current, float target, float delta) {
	if (std::abs(target - current) <= delta)
	{
		return target;
	}
	return current + std::copysignf(delta, target - current);
}

Game::~Game() {
	Game::Finalize();
}