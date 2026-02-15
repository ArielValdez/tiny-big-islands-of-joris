#pragma once
#include <cstdint>

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