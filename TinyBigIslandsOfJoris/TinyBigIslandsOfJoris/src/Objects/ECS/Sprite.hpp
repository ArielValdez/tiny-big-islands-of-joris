#pragma once
#include "../EntityComponentSystem.hpp"
#include "SDL.h"

class Sprite : public Component {
public:
	Vector2 Position;
	Vector2 Size;
	Vector2 Scale;

public:
	Sprite() = default;
	Sprite(const char* path, Vector2 spriteSize) {
		Texture = TextureManager::LoadTexture(path);
		Position = Vector2(0, 0);
		Scale = Vector2(1, 1);

		Size = spriteSize;

		SrcRect = SDL_Rect();
		DestRect = SDL_Rect();
	}

	bool Init() override {
		SrcRect.x = 0;
		SrcRect.y = 0;
		SrcRect.w = Size.X;
		SrcRect.h = Size.Y;

		DestRect.x = 0;
		DestRect.y = 0;
		DestRect.w = Size.X * Scale.X * 2;
		DestRect.h = Size.X * Scale.X * 2;

		return true;
	}

	void Update(double delta) override {
		Position.X = Ent->Position.X;
		Position.Y = Ent->Position.Y;

		DestRect.x = Position.X;
		DestRect.y = Position.Y;
	}

	void PhysicsUpdate(double delta) override {

	}

	void Draw() override {
		TextureManager::Draw(Texture, SrcRect, DestRect);
	}

	~Sprite() {
		SDL_DestroyTexture(Texture);
		Texture = nullptr;
	}

private:
	SDL_Texture* Texture;
	SDL_Rect SrcRect;
	SDL_Rect DestRect;
};