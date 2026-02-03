#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureName, SDL_Renderer* ren) {
	Renderer = ren;
	Texture = TextureManager::LoadTexture(textureName, Renderer);
	SrcRect;
	DestRect;
	Position = Vector2(0, 0);

}

GameObject::GameObject(const char* textureName, SDL_Renderer* ren, int x, int y) {
	Renderer = ren;
	Texture = TextureManager::LoadTexture(textureName, Renderer);
	SrcRect;
	DestRect;
	Position = Vector2(x, y);

}

GameObject::GameObject(const char* textureName, SDL_Renderer* ren, Vector2 pos) {
	Renderer = ren;
	Texture = TextureManager::LoadTexture(textureName, Renderer);
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
	SDL_RenderCopy(Renderer, Texture, &SrcRect, &DestRect);
}

void GameObject::Finalize() {

}

GameObject::~GameObject() {
	Finalize();
}