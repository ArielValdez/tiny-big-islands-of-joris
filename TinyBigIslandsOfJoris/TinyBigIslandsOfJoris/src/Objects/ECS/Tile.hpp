#pragma once
#include "SDL.h"
#include "../EntityComponentSystem.hpp"
#include "Sprite.hpp"
#include "Transform.hpp"
#include "../Vector2.hpp"
#include "../Enums/CollissionLayerMap.hpp"

class Tile : public Component {
public:
	SDL_Rect Rect;

	Transform* Transform;
	Sprite* Texture;

	int TileId;

	const char* TexturePath;

public:
	Tile() = default;
	Tile(int x, int y, int w, int h, int id) {
		Rect.x = x;
		Rect.y = y;
		Rect.w = w;
		Rect.h = h;

		TileId = id;

		switch (TileId)
		{
		case 0:
			TexturePath = "Assets/water.jpg";
			break;
		case 1:
			TexturePath = "Assets/dirt.jpg";
			break;
		case 2:
			TexturePath = "Assets/grass.jpg";
			break;
		default:
			break;
		}
	}

	Tile(Vector2 size, Vector2 scale, int id) {
		Rect.x = size.X;
		Rect.y = size.Y;
		Rect.w = scale.X;
		Rect.h = scale.Y;

		TileId = id;
	}

	bool Init() override {
		Ent->AddComponent<Sprite>(TexturePath, Vector2(32, 32));
		Texture = &Ent->GetComponent<Sprite>();

		return true;
	}

	~Tile() {

	}
private:

};