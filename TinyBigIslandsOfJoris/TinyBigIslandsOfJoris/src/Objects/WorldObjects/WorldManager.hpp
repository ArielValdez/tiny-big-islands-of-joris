#pragma once
#include "World.hpp"

class WorldManager {
public:
	WorldManager();

	~WorldManager();

private:
	World* Worlds;
};