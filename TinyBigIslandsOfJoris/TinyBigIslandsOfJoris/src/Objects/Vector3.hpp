#pragma once

class Vector3 {
public:
	float X;
	float Y;
	float Z;

public:
	Vector3();
	Vector3(float x, float y, float z);

	void Sum(Vector3 vec);
	Vector3 Normalize();
	float GetMagnitude();

	~Vector3();

	Vector3 operator+ (Vector3 right) {
		Vector3 vec = Vector3(X + right.X, Y + right.Y, Z + right.Z);

		return vec;
	}

	Vector3 operator- (Vector3 right) {
		Vector3 vec = Vector3(X - right.X, Y - right.Y, Z - right.Z);
		return vec;
	}

	Vector3 operator* (float mag) {
		Vector3 vec = Vector3(X * mag, Y * mag, Z * mag);

		return vec;
	}

	Vector3 operator/ (float mag) {
		Vector3 vec = Vector3(X / mag, Y / mag, Z / mag);

		return vec;
	}
};