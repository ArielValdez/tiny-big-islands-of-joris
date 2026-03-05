#pragma once
#include <SDL.h>
#include "../Stats.hpp"
#include "../Objects/ECS/Player.hpp"
#include "../Objects/ECS/Sprite.hpp"

class Controller {
public:
	Player* PlayerEntity;

public:
	virtual bool Init(Player* player) {
		PlayerEntity = player;

		return true;
	}

	virtual void Update(double delta, const SDL_Event& sdlEvent, Sprite* spriteAnim, const Uint8* action) {

	}

	virtual void PostUpdate(double delta) {

	}
};