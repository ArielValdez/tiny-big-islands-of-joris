#include <fstream>
#include "TileMap.hpp"
#include "../Game.hpp"

TileMap::TileMap() {
	//LoadMap(lvl1);
}

void TileMap::LoadMap(std::string path, int sizex, int sizey, int mapW, int mapH) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (size_t y = 0; y < sizey; y++)
	{
		for (size_t x = 0; x < sizex; x++)
		{
			mapFile.get(tile);
			int i = atoi(&tile);
			Game::AddTile(i, x * mapW * 2, y * mapH * 2, mapW, mapH);
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void TileMap::LoadMap(std::string path, Vector2 size, Vector2 widthHeight) {
	LoadMap(path, size.X, size.Y, widthHeight.X, widthHeight.Y);
}

TileMap::~TileMap() {
}