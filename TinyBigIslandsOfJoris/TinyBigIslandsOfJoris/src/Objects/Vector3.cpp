#include <cmath>
#include "Vector3.hpp"

Vector3::Vector3() {
	X = 0;
	Y = 0;
	Z = 0;
}

Vector3::Vector3(float x, float y, float z) {
	X = x;
	Y = y;
	Z = z;
}

void  Vector3::Sum(Vector3 vec) {
	X += vec.X;
	Y += vec.Y;
	Z += vec.Z;
}

Vector3 Vector3::Normalize() {
	Vector3 vec = Vector3(X, Y, Z);
	return vec / GetMagnitude();
}

float Vector3::GetMagnitude() {
	float mag = 0;
	mag = std::sqrtf(X * X + Y * Y + Z * Z);
	return mag;
}

Vector3::~Vector3() {

}