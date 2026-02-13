#include <cmath>
#include "Vector2.hpp"

Vector2::Vector2() {
	X = 0;
	Y = 0;
}

Vector2::Vector2(float x, float y) {
	X = x;
	Y = y;
}

void  Vector2::Sum(Vector2 vec) {
	X += vec.X;
	Y += vec.Y;
}

Vector2 Vector2::Normalize() {
	Vector2 vec = Vector2(X, Y);
	return vec / GetMagnitude();
}

float Vector2::GetMagnitude() {
	float mag = 0;
	mag = std::sqrtf(X * X + Y * Y);
	return mag;
}

std::ostream& operator<< (std::ostream& stream, const Vector2& vec) {
	stream << "(" << vec.X << ", " << vec.Y << ")";
	return stream;
}

Vector2::~Vector2() {

}