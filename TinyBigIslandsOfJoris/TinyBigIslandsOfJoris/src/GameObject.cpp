#include "Game.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureName) {
	Texture = TextureManager::LoadTexture(textureName);
	SrcRect;
	DestRect;
	Position = Vector2(0, 0);

}

GameObject::GameObject(const char* textureName, int x, int y) {
	Texture = TextureManager::LoadTexture(textureName);
	SrcRect;
	DestRect;
	Position = Vector2(x, y);

}

GameObject::GameObject(const char* textureName, Vector2 pos) {
	Texture = TextureManager::LoadTexture(textureName);
	SrcRect;
	DestRect;
	Position = pos;

}

void GameObject::Update(float delta) {
	Position.X++;
	Position.Y++;

	SrcRect.h = 32;
	SrcRect.w = 32;
	SrcRect.x = 0;
	SrcRect.y = 0;

	DestRect.x = Position.X;
	DestRect.y = Position.Y;
	DestRect.w = SrcRect.w * 2;
	DestRect.h = SrcRect.h * 2;
}

void GameObject::PhysicsUpdate(float delta) {

}

void GameObject::Render() {
	SDL_RenderCopy(Game::Renderer, Texture, &SrcRect, &DestRect);
}

void GameObject::Finalize() {

}

GameObject::~GameObject() {
	Finalize();
}