#pragma once
#include "Chunk.hpp"

class World {
public:
	World();

	~World();
private:
	bool IsActive;

	Chunk* Chunks;
};