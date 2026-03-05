#pragma once
#include <SDL.h>
#include "Player.hpp"
#include "Sprite.hpp"
#include "../EntityComponentSystem.hpp"
#include "../../Stats.hpp"
#include "../../ControllerTypes/PlatformerController.hpp"
#include "../../ControllerTypes/MouseController.hpp"

class KeyboardController : public Component {
public:
	const Uint8* KeysPressed;
	Stats* Stat;
	SDL_Event SdlEvent;

	Sprite* SpriteAnim;

public:
	KeyboardController() {
		KeysPressed = nullptr;
		Stat = nullptr;
		SpriteAnim = nullptr;

		SdlEvent = SDL_Event();
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

		Platformer.Init(((Player*)Ent));
		Mouse.Init(((Player*)Ent));

		SpriteAnim = &Ent->GetComponent<Sprite>();

		return true;
	}

	void Update(double delta) override {
		Platformer.Update(delta, SdlEvent, SpriteAnim, KeysPressed);
		Mouse.Update(delta, SdlEvent, SpriteAnim, 0);
	}

	void PhysicsUpdate(double delta) override {
		//Ent->Position = Ent->Position + Ent->Velocity;
		Platformer.PostUpdate(delta);
		Mouse.PostUpdate(delta);
	}

	void HandlerEvent(const SDL_Event& sdlEvent) override {
		KeysPressed = SDL_GetKeyboardState(NULL);
		SdlEvent = sdlEvent;
	}

	~KeyboardController() {

	}
private:
	PlatformerController Platformer;
	MouseController Mouse;
};