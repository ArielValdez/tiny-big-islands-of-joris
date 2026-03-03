#pragma once

enum JobClass : size_t {
	NONE = 0,
	REAPER = 1, // MELEE
	SCOUT = 2, // RANGER
	BISHOP = 4, // HEALER
	SAGE = 8, // MAGE
	ARTIFICER = 16 // SUMMON
};