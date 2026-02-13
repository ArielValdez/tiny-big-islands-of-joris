#pragma once
#include "../EntityComponentSystem.hpp"
#include "SDL.h"
#include "../Vector2.hpp"

class Transform : public Component {
public:
	Vector2 Position;

	Transform() {
		Position = Vector2(0.f, 0.f);
	}

	Transform(float x, float y) {
		Position = Vector2(x, y);
	}

	void Update(double delta) override {

	}
};