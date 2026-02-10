#pragma once
#include "../EntityComponentSystem.hpp"
#include "SDL.h"

class Controller : public Component {
public:

public:
	Controller() {
	}

	bool Init() {
		return true;
	}

	void Update(float delta) override {
		if (KeysPressed[SDL_SCANCODE_SPACE])
		{
			std::cout << "Pressing SPACE" << std::endl;
		}
		if (KeysPressed[SDL_SCANCODE_W])
		{
			Ent->Position.Y += -10;
		}
		if (KeysPressed[SDL_SCANCODE_S])
		{
			Ent->Position.Y += 10;
		}
		if (KeysPressed[SDL_SCANCODE_A])
		{
			Ent->Position.X += -10;
		}
		if (KeysPressed[SDL_SCANCODE_D])
		{
			Ent->Position.X += 10;
		}
	}

	void PhysicsUpdate(float delta) override {

	}

	void HandlerEvent(SDL_Event sdlEvent) override {
		KeysPressed = SDL_GetKeyboardState(NULL);
	}

	~Controller() {

	}
private:
	const Uint8* KeysPressed;
};