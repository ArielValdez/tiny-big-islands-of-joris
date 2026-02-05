#pragma once
#include "Game.hpp"
#include "Objects/Vector2.hpp"

class GameObject {
public:
	GameObject(const char* textureName);
	GameObject(const char* textureName, int x, int y);
	GameObject(const char* textureName, Vector2 pos);

	void Update(float delta);
	void PhysicsUpdate(float delta);
	void Render();
	void Finalize();

	~GameObject();
private:
	Vector2 Position;

	SDL_Rect SrcRect;
	SDL_Rect DestRect;
	SDL_Texture* Texture;
};