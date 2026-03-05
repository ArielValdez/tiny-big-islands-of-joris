#pragma once
#include <cmath>

struct Calculator {
	static float MoveTowards(float current, float target, float delta);
	static int RoundInt(float s);
	static int FloorInt(float s);
	static int Sign(int n);
	static int Sign(float n);
};