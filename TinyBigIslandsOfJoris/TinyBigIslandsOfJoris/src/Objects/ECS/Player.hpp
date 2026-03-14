#pragma once
#include <SDL.h>
#include "../EntityComponentSystem.hpp"
#include "../../Stats.hpp"
#include "../Inventory/Inventory.hpp"

class Player : public Entity {
public:
	Stats* Stat;
	Inventory* Pocket;
	bool IsGrounded = false;

public:
	Player(Manager& manager);

	void HandleCollission(Entity* other) override {

	}

	~Player();
private:
	Stats DefaultStat;
};