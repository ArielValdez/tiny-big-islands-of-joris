#include "Color.hpp"

Color::Color() {
	R = 0;
	G = 0;
	B = 0;
	A = 1;
	R255 = 0;
	G255 = 0;
	B255 = 0;
	A255 = 255;

	HexCode = "";
}

Color::Color(float r, float g, float b) {
	R = r;
	G = g;
	B = b;
	A = 1;
	R255 = r * 255;
	G255 = g * 255;
	B255 = b * 255;
	A255 = 255;

	HexCode = "";
}

Color::Color(float r, float g, float b, float a) {
	R = r;
	G = g;
	B = b;
	A = a;
	R255 = r * 255;
	G255 = g * 255;
	B255 = b * 255;
	A255 = a * 255;

	HexCode = "";
}

Color::Color(const char* hexCode) {
	HexCode = hexCode;
}