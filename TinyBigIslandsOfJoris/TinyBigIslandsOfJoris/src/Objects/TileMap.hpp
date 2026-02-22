#pragma once
#include <string>
#include "Vector2.hpp"
#include "../Game.hpp"

class TileMap {
public:
	// Props
public:
	TileMap();

	void LoadMap(const char* path, int sizex, int sizey, int mapW, int mapH);
	void LoadMap(const char* path, Vector2 size, Vector2 widthHeight);

	~TileMap();
private:

};