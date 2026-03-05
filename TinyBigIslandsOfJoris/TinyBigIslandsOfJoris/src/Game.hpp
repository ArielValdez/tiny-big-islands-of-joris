#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "WindowManager.h"
#include "Objects/Vector2.hpp"
#include "Calculator.hpp"

class Collider;

class Game {
public:
	WindowManager* WindowRuleManager = NULL;
	static SDL_Renderer* Renderer;
	static std::vector<Collider*> Colliders;
	static bool IsRunning;
	static Vector2 Gravity;
	static SDL_Rect Camera;
	static Vector2 GlobalMousePosition;
	static Vector2 DefaultTileSize;

public:
	Game();

	bool Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void Ready();
	void Update(double delta);
	void PhysicsUpdate(double delta);
	void HandleEvents();
	void HandleCollisions();
	void Render();
	void Finalize();

	bool Running() { return IsRunning; }

	static void AddTile(int id, int srcX, int srcY, int dstX, int dstY, int w, int h, const char* path);
	static void AddTile(int id, Vector2 atlas, Vector2 pos, const char* path);
	static void AddTile(int id, Vector2 atlas, Vector2 pos, Vector2 size, const char* path);

	~Game();
private:
	bool Disposed;
	SDL_Window* Window;
};