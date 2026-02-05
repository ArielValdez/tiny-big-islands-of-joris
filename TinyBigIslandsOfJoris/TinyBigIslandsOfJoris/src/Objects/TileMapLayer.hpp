#pragma once
#include "Vector2.hpp"

class TileMapLayer {
public:
	TileMapLayer();


	~TileMapLayer();
private:
	Vector2 AtlasCoords;
};