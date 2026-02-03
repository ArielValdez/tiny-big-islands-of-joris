#pragma once

struct Vector2 {
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	float X;
	float Y;

	Vector2 operator+ (Vector2 right) {
		Vector2 vec = Vector2();
		vec.X = X + right.X;
		vec.Y = Y + right.Y;

		return vec;
	}
};