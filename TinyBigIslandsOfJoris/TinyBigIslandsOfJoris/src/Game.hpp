#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "WindowManager.h"
#include "Objects/Vector2.hpp"

class Collider;

class Game {
public:
	WindowManager* WindowRuleManager = NULL;
	static SDL_Renderer* Renderer;
	static std::vector<Collider*> Colliders;
	static bool IsRunning;
	static SDL_Rect Camera;

public:
	Game();

	bool Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void Ready();
	void Update(double delta);
	void PhysicsUpdate(double delta);
	void HandleEvents();
	void Render();
	void Finalize();

	bool Running() { return IsRunning; }

	static void AddTile(int id, int srcX, int srcY, int dstX, int dstY, int w, int h, const char* path);
	static void AddTile(int id, Vector2 atlas, Vector2 pos, const char* path);
	static void AddTile(int id, Vector2 atlas, Vector2 pos, Vector2 size, const char* path);
	static float MoveTowards(float current, float target, float delta);

	~Game();
private:
	bool Disposed;
	SDL_Window* Window;
};