#pragma once

struct Color {
	Color();
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	Color(const char* hexCode);

	float R; // Red Channel
	float G; // Green Channel
	float B; // Blue Channel
	float A; // Alpha Channel

	float R255; // Red Channel
	float G255; // Green Channel
	float B255; // Blue Channel
	float A255; // Alpha Channel

	const char* HexCode;
};