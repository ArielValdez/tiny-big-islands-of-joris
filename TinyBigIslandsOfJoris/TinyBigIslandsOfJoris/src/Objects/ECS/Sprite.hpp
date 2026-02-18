#pragma once
#include "../EntityComponentSystem.hpp"
#include "SDL.h"
#include "Animation.hpp"
#include <map>

class Sprite : public Component {
public:
	Vector2 Position;
	Vector2 Size;
	Vector2 Scale;

	int AnimIdx = 0;

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

	Sprite(const char* path, Vector2 spriteSize, int frames, int delay) {
		Texture = TextureManager::LoadTexture(path);
		Position = Vector2(0, 0);
		Scale = Vector2(1, 1);

		Size = spriteSize;

		SrcRect = SDL_Rect();
		DestRect = SDL_Rect();

		IsAnimated = true;

		Animation reset = Animation(0, frames, delay);

		Animations.emplace("reset", reset);
	}

	Sprite(const char* path, Vector2 spriteSize, std::map<const char*, Animation> anims) {
		Texture = TextureManager::LoadTexture(path);
		Position = Vector2(0, 0);
		Scale = Vector2(1, 1);

		Size = spriteSize;

		SrcRect = SDL_Rect();
		DestRect = SDL_Rect();

		IsAnimated = true;

		Animations = anims;
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
		if (IsAnimated)
		{
			SrcRect.x = SrcRect.w * static_cast<int>((SDL_GetTicks() / Delay) % Frames);
			SrcRect.y = AnimIdx * Size.Y;
		}

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

	void Play(char* animName) {
		Delay = Animations[animName].Delay;
		Frames = Animations[animName].Frames;
		AnimIdx = Animations[animName].Index;
	}

	~Sprite() {
		SDL_DestroyTexture(Texture);
		Texture = nullptr;
	}

private:
	SDL_Texture* Texture;
	SDL_Rect SrcRect;
	SDL_Rect DestRect;

	std::map<const char*, Animation> Animations;

	bool IsAnimated;
	int Frames;
	int Delay;
};