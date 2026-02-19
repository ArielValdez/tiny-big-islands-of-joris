#pragma once
#include "../EntityComponentSystem.hpp"
#include "../../Stats.hpp"
#include "Player.hpp"
#include "Sprite.hpp"
#include "SDL.h"

class KeyboardController : public Component {
public:

public:
	KeyboardController() {
		KeysPressed = nullptr;
		Stat = nullptr;
		SpriteAnim = nullptr;
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

		SpriteAnim = &Ent->GetComponent<Sprite>();

		return true;
	}

	void Update(double delta) override {

		if (SdlEvent.type & SDL_KEYDOWN)
		{
			if (KeysPressed[SDL_SCANCODE_SPACE])
			{
				std::cout << "Pressing SPACE" << std::endl;
			}
			if (KeysPressed[SDL_SCANCODE_W])
			{
				Ent->Velocity.Y = -Stat->Speed * delta;
				SpriteAnim->Play("walk");
				//Ent->Position.Y += Ent->Velocity.Y;
			}
			if (KeysPressed[SDL_SCANCODE_S])
			{
				Ent->Velocity.Y = Stat->Speed * delta;
				SpriteAnim->Play("walk");
				//Ent->Position.Y += Ent->Velocity.Y;
			}
			if (KeysPressed[SDL_SCANCODE_A])
			{
				Ent->Velocity.X = -Stat->Speed * delta;
				SpriteAnim->Play("walk");
				SpriteAnim->RenderFlip = SDL_FLIP_HORIZONTAL;
				//Ent->Position.X += Ent->Velocity.X;
			}
			if (KeysPressed[SDL_SCANCODE_D])
			{
				Ent->Velocity.X = Stat->Speed * delta;
				SpriteAnim->Play("walk");
				SpriteAnim->RenderFlip = SDL_FLIP_NONE;
				//Ent->Position.X += Ent->Velocity.X;
			}
		}
		if (SdlEvent.type == SDL_KEYUP)
		{
			Ent->Velocity = Vector2();
			SpriteAnim->Play("idle");
		}
	}

	void PhysicsUpdate(double delta) override {
		Ent->Position = Ent->Position + Ent->Velocity;
	}

	void HandlerEvent(const SDL_Event& sdlEvent) override {
		KeysPressed = SDL_GetKeyboardState(NULL);
		SdlEvent = sdlEvent;
	}

	~KeyboardController() {

	}
private:
	const Uint8* KeysPressed;
	Stats* Stat;
	SDL_Event SdlEvent;

	Sprite* SpriteAnim;

};