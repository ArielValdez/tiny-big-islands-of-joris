//#include "Collission.hpp"
#include "Collider.hpp"

bool Collission::AABB(const Vector2& a, const Vector2& b) {
	return (a.X /*+ rectA.w*/ >= b.X &&
			b.X /*+ rectB.w*/ >= a.X &&
			a.Y /*+ rectA.h*/ >= b.Y &&
			b.Y /*+ rectB.h*/ >= a.Y
		);
}

bool Collission::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	/*return (rectA.x + rectA.w >= rectB.x &&
			rectB.x + rectB.w >= rectA.x &&
			rectA.y + rectA.h >= rectB.y &&
			rectB.y + rectB.h >= rectA.y
		);*/
	return static_cast<bool>(SDL_HasIntersection(&rectA, &rectB));
}

bool Collission::AABB(Collider* colliderA, Collider* colliderB) {
	if (colliderA->Layer & colliderB->Map) {
		return AABB(colliderA->Rect, colliderB->Rect);
	}

	return false;
}