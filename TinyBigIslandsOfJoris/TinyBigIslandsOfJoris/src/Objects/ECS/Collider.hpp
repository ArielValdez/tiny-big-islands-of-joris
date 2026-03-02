#pragma once
#include <SDL.h>
#include <functional>
#include "../Enums/CollissionLayerMap.hpp"
#include "../EntityComponentSystem.hpp"
#include "../../Game.hpp"
#include "Player.hpp"

class Collider;
class Collission;

class Collission {
public:
	static bool AABB(const Vector2& a, const Vector2& b);
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(Collider* colliderA, Collider* colliderB);
};

class Collider : public Component {
public:
	CollissionMapLayer Layer;
	CollissionMapLayer Map;
	SDL_Rect Rect;

	Vector2 RectPos;

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

		Remainder = Vector2();

		XCollision = false;
		YCollision = false;
	}

	Collider(Vector2 size) {
		Layer = CollissionMapLayer::AIR;
		Map = CollissionMapLayer::AIR;
		Size = size;

		Rect = SDL_Rect();

		Monitoring = true;
		Monitorable = true;

		Remainder = Vector2();

		XCollision = false;
		YCollision = false;
	}

	Collider(Vector2 size, CollissionMapLayer layer, CollissionMapLayer map) {
		Layer = layer;
		Map = map;
		Size = size;

		Rect = SDL_Rect();

		Monitoring = true;
		Monitorable = true;

		Remainder = Vector2();

		XCollision = false;
		YCollision = false;
	}

	bool Init() override {

		Game::Colliders.push_back(this);
		return true;
	}

	void Update(double delta) override {
		Rect.x = Ent->Position.X;
		Rect.y = Ent->Position.Y;
		Rect.w = Size.X * 2;
		Rect.h = Size.Y * 2;

		RectPos = Vector2(Rect.x + Rect.w, Rect.y + Rect.h);
	}

#pragma region Collider Functions
	void MoveX(float amount, std::vector<Entity*> solids, std::function<void(void)> onCollide)
	{
		Remainder.X += amount;
		int move = Calculator::RoundInt(Remainder.X);
		if (move != 0)
		{
			Remainder.X -= move;
			int sign = Calculator::Sign(move);
			Rect.x += PixelsCheck.X * sign;

			while (move != 0)
			{
				for (Entity* solid : solids)
				{
					Collider* solidCollider = &solid->GetComponent<Collider>();
					if (solidCollider == nullptr) continue;

					if (Collission::AABB(this, solidCollider))
					{
						XCollision = true;

						// There is no Solid immediately beside us
						// Hit a solid!
						if (onCollide != nullptr) {
							onCollide();
							Rect.x -= PixelsCheck.X * sign;
							return;
						}

						if (Ent->Velocity.X >= 0.0f)
						{
							Ent->Position.X = solidCollider->Rect.x - Rect.w;
						}
						else if (Ent->Velocity.X < 0.0f)
						{
							Ent->Position.X = solidCollider->RectPos.X;
						}

						Ent->Velocity.X = 0;
						Rect.x -= PixelsCheck.X * sign;
						return;
					}
					else
					{
						XCollision = false;
					}
				}

				Ent->Position.X += amount;
				move -= sign;
			}
		}
	}

	void MoveY(float amount, std::vector<Entity*> solids, std::function<void(void)> onCollide)
	{
		Remainder.Y += amount;

		int move = Calculator::RoundInt(Remainder.Y);
		Player* player = static_cast<Player*>(Ent);

		if (move != 0)
		{
			Remainder.Y -= move;
			int sign = Calculator::Sign(move);

			Rect.y += PixelsCheck.Y * sign;

			while (move != 0)
			{
				//if (Ent->Velocity.Y != 0)

				for (Entity* solid : solids)
				{
					Collider* solidCollider = &solid->GetComponent<Collider>();
					if (solidCollider == nullptr) continue;

					if (Collission::AABB(this, solidCollider))
					{
						//std::cout << "Collision happend" << std::endl;
						YCollision = true;

						// There is no Solid immediately beside us
						// Hit a solid!
						if (onCollide != nullptr) {
							onCollide();
							Rect.y -= PixelsCheck.Y * sign;
							return;
						}

						if (Ent->Velocity.Y > 0.0f)
						{
							Ent->Position.Y = solidCollider->Rect.y - Rect.h;
							if (player != nullptr) {
								player->IsGrounded = true;
							}
						}
						else if (Ent->Velocity.Y < 0.0f)
						{
							Ent->Position.Y = solidCollider->RectPos.Y;
						}

						Ent->Velocity.Y = 0.0f;
						Rect.y -= PixelsCheck.Y * sign;
						return;
					}
					else
					{
						if (player != nullptr)
						{
							player->IsGrounded = false;
						}
						YCollision = false;
					}
				}

				Ent->Position.Y += sign;
				move -= sign;
			}

			Rect.y -= PixelsCheck.Y * sign;
		}
	}

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
	Vector2 Remainder;
	const Vector2 PixelsCheck = Vector2(8, 8);
	Vector2 Size;

	bool XCollision;
	bool YCollision;
};