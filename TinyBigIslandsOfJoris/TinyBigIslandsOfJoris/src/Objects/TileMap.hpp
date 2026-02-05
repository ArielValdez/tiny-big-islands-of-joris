#pragma once
#include "Vector2.hpp"
#include "../Game.hpp"

class TileMap {
public:
	// Props
public:
	TileMap();

	void LoadMap(int arr[20][25]);
	void DrawMap();

	~TileMap();
private:
	// Props
	Vector2 AtlasCoords;
	SDL_Rect SrcRect;
	SDL_Rect DestRect;

	SDL_Texture* Dirt;
	SDL_Texture* Grass;
	SDL_Texture* Water;

	int map[20][25];

	size_t TileSize;
};