#pragma once

struct Stats {
	// Movement
	float Speed = 2.1f;
	float Acceleration = 1.f;
	float Deceleration = 0.5f;
	float JumpSpeed = -12.5f;
	float FallSpeed = 0.4f;
	float FlightTime = 15.f;

	// Bulding
	int BuildingDistance = 7; // Tiles from player
};