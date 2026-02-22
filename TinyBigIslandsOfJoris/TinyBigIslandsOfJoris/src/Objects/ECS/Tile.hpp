#pragma once
#include "SDL.h"
#include "../EntityComponentSystem.hpp"
#include "../Vector2.hpp"
#include "../Enums/CollissionLayerMap.hpp"

class Tile : public Component {
public:
	SDL_Texture* Texture;

	int TileId;

public:
	Tile() = default;
	Tile(int srcX, int srcY, int dstX, int dstY, int w, int h, int id, const char* path) {
		SrcRect.x = srcX;
		SrcRect.y = srcY;
		SrcRect.w = w;
		SrcRect.h = h;

		DstRect.x = dstX;
		DstRect.y = dstY;
		DstRect.w = w * 2;
		DstRect.h = h * 2;

		TileId = id;

		TexturePath = path;
		Texture = TextureManager::LoadTexture(path);
	}

	bool Init() override {
		Ent->Position.X = SrcRect.x;
		Ent->Position.Y = SrcRect.y;
		return true;
	}

	void Draw() override
	{
		TextureManager::Draw(Texture, SrcRect, DstRect);
	}

	~Tile() {
		SDL_DestroyTexture(Texture);
		Texture = nullptr;
	}
private:
	const char* TexturePath;

	SDL_Rect SrcRect;
	SDL_Rect DstRect;
};