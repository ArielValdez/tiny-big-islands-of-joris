#pragma once
#include "../EntityComponentSystem.hpp"
#include "SDL.h"

class Sprite : public Component {
public:

public:
	Sprite() = default;
	Sprite(const char* path, Vector2 spriteSize) {
		Texture = TextureManager::LoadTexture(path);
		Size = spriteSize;
		Position = Vector2(0, 0);

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
		DestRect.w = Size.X * 2;
		DestRect.h = Size.Y * 2;

		return true;
	}

	void Update(float delta) override {
		Position.X += 1;
		Position.Y += 1;

		DestRect.x = Position.X;
		DestRect.y = Position.Y;

		std::cout << Position.X << ", " << Position.Y << std::endl;
	}

	void PhysicsUpdate(float delta) override {

	}

	void Draw() override {
		TextureManager::Draw(Texture, SrcRect, DestRect);
	}

private:
	Vector2 Position;
	Vector2 Size;
	SDL_Texture* Texture;
	SDL_Rect SrcRect;
	SDL_Rect DestRect;
};