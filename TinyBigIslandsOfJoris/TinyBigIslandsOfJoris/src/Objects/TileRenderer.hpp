#pragma once
#include <string>
#include "Vector2.hpp"
#include "../Game.hpp"

class TileRenderer {
public:
	// Props
public:
	TileRenderer();

	static Vector2 GetTiledPosition(Vector2 globalPosition);

	void LoadMap(const char* path, int sizex, int sizey, int mapW, int mapH);
	void LoadMap(const char* path, Vector2 size, Vector2 widthHeight);

	~TileRenderer();
private:

};