#pragma once
#include "../EntityComponentSystem.hpp"
#include "SDL.h"
#include "../../Stats.hpp"

class Player : public Entity {
public:
	Stats* Stat;

public:
	Player(Manager& manager);

	~Player();
private:

};