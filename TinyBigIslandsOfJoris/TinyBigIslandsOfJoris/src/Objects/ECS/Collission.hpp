#pragma once
#include "SDL.h"
#include "Collider.hpp"

class Collission {
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(Collider* colliderA, Collider* colliderB);
};