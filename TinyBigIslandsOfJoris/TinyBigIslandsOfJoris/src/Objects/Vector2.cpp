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

Vector2::~Vector2() {

}