#include "Collission.hpp"

bool Collission::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	return (rectA.x + rectA.w >= rectB.x &&
			rectB.x + rectB.w >= rectA.x &&
			rectA.y + rectA.h >= rectB.y &&
			rectB.y + rectB.h >= rectA.y
		);
}

bool Collission::AABB(Collider* colliderA, Collider* colliderB) {
	if (colliderA->Layer & colliderB->Map) {
		return AABB(colliderA->Rect, colliderB->Rect);
	}

	return false;
}