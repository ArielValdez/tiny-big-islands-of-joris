#pragma once
#include "../EntityComponentSystem.hpp"
#include "../../Stats.hpp"
#include "Player.hpp"
#include "SDL.h"

class Controller : public Component {
public:

public:
	Controller() {
		KeysPressed = NULL;
		Stat = new Stats();
	}

	bool Init() {
		Stats* stats = ((Player*)Ent)->Stat;
		if (stats != nullptr) {
			Stat = nullptr;
		}
		else
		{
			stats = new Stats();
			if (stats->Speed <= 0)
			{
				stats->Speed = 10;
			}
		}
		Stat = stats;
		stats = nullptr;
		return true;
	}

	void Update(double delta) override {
		if (KeysPressed[SDL_SCANCODE_SPACE])
		{
			std::cout << "Pressing SPACE" << std::endl;
		}
		if (KeysPressed[SDL_SCANCODE_W])
		{
			Ent->Velocity.Y = -Stat->Speed * delta;
			Ent->Position.Y += Ent->Velocity.Y;
		}
		if (KeysPressed[SDL_SCANCODE_S])
		{
			Ent->Velocity.Y = Stat->Speed * delta;
			Ent->Position.Y += Ent->Velocity.Y;
		}
		if (KeysPressed[SDL_SCANCODE_A])
		{
			Ent->Velocity.X = -Stat->Speed * delta;
			Ent->Position.X += Ent->Velocity.X;
		}
		if (KeysPressed[SDL_SCANCODE_D])
		{
			Ent->Velocity.X = Stat->Speed * delta;
			Ent->Position.X += Ent->Velocity.X;
		}
	}

	void PhysicsUpdate(double delta) override {

	}

	void HandlerEvent(SDL_Event sdlEvent) override {
		KeysPressed = SDL_GetKeyboardState(NULL);
	}

	~Controller() {

	}
private:
	const Uint8* KeysPressed;
	Stats* Stat;

private:

};