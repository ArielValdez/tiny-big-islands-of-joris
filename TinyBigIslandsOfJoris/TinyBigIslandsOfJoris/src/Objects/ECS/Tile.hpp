#pragma once
#include "SDL.h"
#include "../EntityComponentSystem.hpp"
#include "../Vector2.hpp"
#include "../Enums/CollissionLayerMap.hpp"

class Tile : public Component {
public:
	SDL_Texture* Texture;
	Vector2 AtlasCoords;
	Vector2 TilePosition;
	int TileId;

public:
	Tile() = default;
	Tile(int srcX, int srcY, int dstX, int dstY, int w, int h, int id, const char* path) {
		SrcRect.x = srcX;
		SrcRect.y = srcY;
		SrcRect.w = w;
		SrcRect.h = h;

		DstRect.x = dstX - (w / 2);
		DstRect.y = dstY - (h / 2);
		DstRect.w = w * 2;
		DstRect.h = h * 2;

		TileId = id;

		TexturePath = path;
		Texture = TextureManager::LoadTexture(path);
	}

	bool Init() override {
		Ent->Position.X = SrcRect.x;
		Ent->Position.Y = SrcRect.y;

		AtlasCoords = Vector2(SrcRect.x / SrcRect.w, SrcRect.y / SrcRect.h);
		TilePosition = Vector2(DstRect.x / DstRect.w, DstRect.y / DstRect.h);

		return true;
	}

	void Draw() override
	{
		TextureManager::Draw(Texture, SrcRect, DstRect);
	}

	void Draw(SDL_Rect& camera) override
	{
		TextureManager::Draw(Texture, SrcRect, DstRect, camera, SDL_FLIP_NONE);
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