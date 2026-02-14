#pragma once
#include <cstdint>
#include "../EntityComponentSystem.hpp"
#include "SDL.h"

enum class CollissionMapLayer : uint8_t {
	AIR = 0,
	PLAYER = 1,
	ENEMY = 2,
	WORLD_DEFAULT = 4,
	PLAYER_PROJECTILE = 8,
	ENEMY_PROJECTILE = 16,
	TRAP = 32,

};

constexpr CollissionMapLayer operator|(CollissionMapLayer lhs, CollissionMapLayer rhs) {
	return static_cast<CollissionMapLayer>(
		static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs)
		);
}

// Overload the bitwise AND operator
constexpr uint8_t operator&(CollissionMapLayer lhs, CollissionMapLayer rhs) {
	return static_cast<uint8_t>(
		static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs)
		);
}

// Overload the bitwise NOT operator
constexpr CollissionMapLayer operator~(CollissionMapLayer rhs) {
	return static_cast<CollissionMapLayer>(~static_cast<uint8_t>(rhs));
}

// Compound assignment operators (optional, but useful)
inline CollissionMapLayer& operator|=(CollissionMapLayer& lhs, CollissionMapLayer rhs) {
	lhs = lhs | rhs;
	return lhs;
}

class Collider : public Component {
public:
	CollissionMapLayer Layer;
	CollissionMapLayer Map;
	SDL_Rect Rect;

	bool Monitoring;
	bool Monitorable;
public:
	Collider() {
		Layer = CollissionMapLayer::AIR;
		Map = CollissionMapLayer::AIR;
		Size = Vector2();

		Rect = SDL_Rect();

		Monitoring = true;
		Monitorable = true;
	}

	Collider(Vector2 size) {
		Layer = CollissionMapLayer::AIR;
		Map = CollissionMapLayer::AIR;
		Size = size;

		Rect = SDL_Rect();

		Monitoring = true;
		Monitorable = true;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="size"></param>
	/// <param name="layer"></param>
	/// <param name="map"></param>
	Collider(Vector2 size, CollissionMapLayer layer, CollissionMapLayer map) {
		Layer = layer;
		Map = map;
		Size = size;

		Rect = SDL_Rect();

		Monitoring = true;
		Monitorable = true;
	}

	bool Init() override {
		return true;
	}

	void Update(double delta) override {
		Rect.x = Ent->Position.X;
		Rect.y = Ent->Position.Y;
		Rect.w = Size.X;
		Rect.h = Size.Y;
	}

#pragma region Collider Functions
	void OnColliderEntered() {

	}

	void OnColliderExited() {

	}
#pragma endregion

	~Collider() {
		Layer = CollissionMapLayer::AIR;
		Map = CollissionMapLayer::AIR;
	}

private:
	Vector2 Size;
};