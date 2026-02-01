#pragma once
#include <SDL.h>
#include "WindowManager.h"

class Game {
public:
	// Props
public:
	Game();

	bool Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void Ready();
	void Update(float delta);
	void PhysicsUpdate(float delta);
	void HandleEvents();
	void Render();
	void Finalize();

	bool Running() { return IsRunning; }

	~Game();
private:
	bool IsRunning;
	bool Disposed;
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	WindowManager* WindowRuleManager = NULL;
};