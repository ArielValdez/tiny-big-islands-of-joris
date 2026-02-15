#pragma once
#include "../Enums/CollissionLayerMap.hpp"
#include "../EntityComponentSystem.hpp"
#include "SDL.h"
#include "../../Game.hpp"

class Collider : public Component {
public:
	CollissionMapLayer Layer;
	CollissionMapLayer Map;
	SDL_Rect Rect;

	bool Monitoring;
	bool Monitorable;
public:
	Collider() {
		Layer = CollissionMapLayer::AIR;
		Map = CollissionMapLayer::AIR;
		Size = Vector2();

		Rect = SDL_Rect();

		Monitoring = true;
		Monitorable = true;
	}

	Collider(Vector2 size) {
		Layer = CollissionMapLayer::AIR;
		Map = CollissionMapLayer::AIR;
		Size = size;

		Rect = SDL_Rect();

		Monitoring = true;
		Monitorable = true;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="size"></param>
	/// <param name="layer"></param>
	/// <param name="map"></param>
	Collider(Vector2 size, CollissionMapLayer layer, CollissionMapLayer map) {
		Layer = layer;
		Map = map;
		Size = size;

		Rect = SDL_Rect();

		Monitoring = true;
		Monitorable = true;
	}

	bool Init() override {

		Game::Colliders.push_back(this);
		return true;
	}

	void Update(double delta) override {
		Rect.x = Ent->Position.X;
		Rect.y = Ent->Position.Y;
		Rect.w = Size.X;
		Rect.h = Size.Y;
	}

#pragma region Collider Functions
	void OnColliderEntered() {

	}

	void OnColliderExited() {

	}
#pragma endregion

	~Collider() {
		Layer = CollissionMapLayer::AIR;
		Map = CollissionMapLayer::AIR;
	}

private:
	Vector2 Size;
};