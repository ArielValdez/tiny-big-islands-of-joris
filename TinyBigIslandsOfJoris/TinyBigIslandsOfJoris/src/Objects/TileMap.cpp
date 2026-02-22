#include <fstream>
#include "TileMap.hpp"
#include "../Game.hpp"

TileMap::TileMap() {
	//LoadMap(lvl1);
}

void TileMap::LoadMap(const char* path, int sizex, int sizey, int mapW, int mapH) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX;
	int srcY;

	for (size_t y = 0; y < sizey; y++)
	{
		for (size_t x = 0; x < sizex; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * mapH;
			mapFile.get(c);
			srcX = atoi(&c) * mapW;

			Game::AddTile(atoi(&c), srcX, srcY, x * mapW * 2, y * mapH * 2, mapW, mapH, path);
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void TileMap::LoadMap(const char* path, Vector2 size, Vector2 widthHeight) {
	LoadMap(path, size.X, size.Y, widthHeight.X, widthHeight.Y);
}

TileMap::~TileMap() {
}