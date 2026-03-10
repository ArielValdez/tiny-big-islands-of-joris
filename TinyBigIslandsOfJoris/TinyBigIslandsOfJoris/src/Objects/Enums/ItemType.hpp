#pragma once

enum ItemType : size_t {
	NONE = 0,
	// Equipment
	HELMET = 1,
	CHEST = 2,
	LEGGINGS = 4,
	RELIC = 8,
	HANDS = 16,
	INGREDIENT = 32,
	PLACEABLE = 64,
	CONSUMABLE = 128,
	MONEY = 256
};