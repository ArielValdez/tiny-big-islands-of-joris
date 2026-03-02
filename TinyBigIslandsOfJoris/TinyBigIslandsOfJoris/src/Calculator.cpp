#include "Calculator.hpp"

float Calculator::MoveTowards(float current, float target, float delta) {
	if (std::abs(target - current) <= delta)
	{
		return target;
	}
	return current + std::copysignf(delta, target - current);
}

int Calculator::RoundInt(float s) {
	return static_cast<int>(std::round(s));
}

int Calculator::Sign(int n) {
	return (n > 0) - (n < 0);
}

int Calculator::Sign(float n) {
	if (n == 0.f)
	{
		return 0;
	}
	return n > 0.f ? 1 : -1;
}