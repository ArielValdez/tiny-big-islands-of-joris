#include "Game.hpp"
#include "Calculator.hpp"
#include "TextureManager.hpp"
#include "Objects/TileRenderer.hpp"
#include "Objects/ECS/Entities.hpp"
#include "Objects/ECS/Components.hpp"
#include "Objects/Enums/GroupLabels.hpp"

TileRenderer* map;
Vector2 Game::Gravity;

Manager manager;

#pragma region Static
SDL_Renderer* Game::Renderer = nullptr;
std::vector<Collider*> Game::Colliders;
ImGuiContext* Game::ImGuiContext;
SDL_Rect Game::Camera = { 0, 0, 500, 500 };
Vector2 Game::GlobalMousePosition = Vector2(0, 0);
Vector2 Game::DefaultTileSize = Vector2(32, 32);
bool Game::IsRunning = false;
//ThreadPool Game::Pool;
#pragma endregion

Player& player = (Player&)(manager.AddEntity<Player>());
Entity& wallTest = manager.AddEntity();
Entity& wallTest2 = manager.AddEntity();

bool showSomePanel = true;

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

	// Init Dear ImGUI
	if (!IMGUI_CHECKVERSION())
	{
		return false;
	}
	Game::ImGuiContext = ImGui::CreateContext();
	ImGuiIO& io{ ImGui::GetIO() };
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	// SDL2 Window
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

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(
		Game::Window,
		Game::Renderer
	);
	ImGui_ImplSDLRenderer2_Init(
		Game::Renderer
	);

	map = new TileRenderer();
	map->LoadMap("Assets/map.map", 32, 32, 32, 32);

	player.AddComponent<Collider>(
		Vector2(32, 32),
		CollissionMapLayer::PLAYER,
		CollissionMapLayer::ENEMY | CollissionMapLayer::WORLD_DEFAULT | CollissionMapLayer::ENEMY_PROJECTILE | CollissionMapLayer::TRAP);
	player.AddComponent<Sprite>("Assets/Alma.png", Vector2(32, 32));
	player.AddComponent<KeyboardController>();
	player.AddGroup(GroupLabels::PLAYERS);

	wallTest.AddComponent<Collider>(
		Vector2(512, 32),
		CollissionMapLayer::WORLD_DEFAULT,
		CollissionMapLayer::PLAYER | CollissionMapLayer::ENEMY | CollissionMapLayer::ENEMY_PROJECTILE);
	wallTest.AddComponent<Sprite>("Assets/dirt.jpg", Vector2(512, 32));
	wallTest.AddGroup(GroupLabels::MAP);

	wallTest.Position = Vector2(0, 512);

	wallTest2.AddComponent<Collider>(
		Vector2(32, 512),
		CollissionMapLayer::WORLD_DEFAULT,
		CollissionMapLayer::PLAYER | CollissionMapLayer::ENEMY | CollissionMapLayer::ENEMY_PROJECTILE);
	wallTest2.AddComponent<Sprite>("Assets/dirt.jpg", Vector2(32, 512));
	wallTest2.AddGroup(GroupLabels::MAP);

	wallTest2.Position = Vector2(1024, -512);

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

void Game::HandleCollisions() {
	auto* playerCollider = &player.GetComponent<Collider>();

	playerCollider->MoveX(player.Velocity.X, tiles, nullptr);
	playerCollider->MoveY(player.Velocity.Y, tiles, nullptr);
}

void Game::ResolveCollisions() {

}

void Game::PhysicsUpdate(double delta) {
	manager.PhysicsUpdate(delta);
}

void Game::HandleEvents() {
	SDL_Event sdlEvent;

	if (SDL_PollEvent(&sdlEvent))
	{
		ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

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

	// ImGui Start Frame
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	// Render "some panel".
	//if (showSomePanel) {
	//	ImGui::Begin("Some panel", &showSomePanel);
	//	ImGui::Text("Hello World");
	//	ImGui::End();
	//}

	// Rendering
	ImGui::Render();

	//manager.Draw(Game::Camera); // TODO Refactor

	// TODO Crear una nueva clase Window, donde se manejarán todos los eventos pertenecientes a la ventana SDL e ImGUI
	/*SDL_SetRenderDrawColor(
		Game::Renderer,
		100, 100, 100, 255
	);*/

	for (auto& t : tiles)
	{
		t->Draw(Game::Camera);
	}

	for (auto& t : players)
	{
		t->Draw(Game::Camera);
	}

	for (auto& t : enemies)
	{
		t->Draw(Game::Camera);
	}

	// Render data through the SDL renderer
	ImGui_ImplSDLRenderer2_RenderDrawData(
		ImGui::GetDrawData(),
		Game::Renderer
	);

	SDL_RenderPresent(Renderer);
}

void Game::Finalize() {
	// Destroy objects
	if (!Disposed) {
		ImGui_ImplSDLRenderer2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

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
	AddTile(id, atlas, pos, Game::DefaultTileSize, path);
}

void Game::AddTile(int id, Vector2 atlas, Vector2 pos, Vector2 size, const char* path) {
	auto& tile = manager.AddEntity();
	tile.AddComponent<Tile>(atlas.X, atlas.Y, pos.X, pos.Y, size.X, size.Y, id, path);
	tile.AddGroup(GroupLabels::MAP);
}

Game::~Game() {
	Game::Finalize();
}