#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "WindowManager.h"
#include "Objects/Vector2.hpp"

class Collider;

class Game {
public:
	WindowManager* WindowRuleManager = NULL;
	static SDL_Renderer* Renderer;
	static std::vector<Collider*> Colliders;

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

	static void AddTile(int id, int x, int y, int w, int h);
	static void AddTile(int id, Vector2 atlas);
	static void AddTile(int id, Vector2 atlas, Vector2 size);

	~Game();
private:
	bool IsRunning;
	bool Disposed;
	SDL_Window* Window;
};