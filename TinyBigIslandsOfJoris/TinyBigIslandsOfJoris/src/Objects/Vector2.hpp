#pragma once

#include <iostream>

class Vector2 {
public:
	float X;
	float Y;


public:
	Vector2();
	Vector2(float x, float y);

	void Sum(Vector2 vec);
	Vector2 Normalize();
	float GetMagnitude();

	~Vector2();

	friend std::ostream& operator<< (std::ostream& stream, const Vector2& vec);

	Vector2 operator+ (Vector2 right) {
		Vector2 vec = Vector2();
		vec.X = X + right.X;
		vec.Y = Y + right.Y;

		return vec;
	}

	Vector2 operator- (Vector2 right) {
		Vector2 vec = Vector2();
		vec.X = X - right.X;
		vec.Y = Y - right.Y;

		return vec;
	}

	Vector2 operator* (float mag) {
		Vector2 vec = Vector2(X, Y);
		vec.X *= mag;
		vec.Y *= mag;

		return vec;
	}

	Vector2 operator/ (float mag) {
		Vector2 vec = Vector2(X, Y);
		vec.X /= mag;
		vec.Y /= mag;

		return vec;
	}
};