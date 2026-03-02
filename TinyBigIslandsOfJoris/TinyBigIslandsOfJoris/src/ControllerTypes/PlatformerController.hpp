#pragma once
#include <SDL.h>
#include "../Stats.hpp"
#include "../Objects/ECS/Player.hpp"

class PlatformerController {
public:
	PlatformerController() {

	}

	bool Init(Player* player) {
		Player = player;
		return true;
	}

	void Update(float delta, const SDL_Event& sdlEvent, Sprite* spriteAnim, const Uint8* keysPressed) {
		// Gravity
		Player->Velocity.Y = Calculator::MoveTowards(Player->Velocity.Y, Game::Gravity.Y, Player->Stat->FallSpeed);

		JustPressed(delta, sdlEvent, spriteAnim, keysPressed);
		Pressed(delta, sdlEvent, spriteAnim, keysPressed);

		SDL_memcpy(PostKeysPressed, keysPressed, SDL_NUM_SCANCODES);
	}

	void PostUpdate(float delta) {
		//std::cout << Player->Velocity << std::endl;
		//Player->Position.X += Player->Velocity.X;
	}

	~PlatformerController() {

	}

private:
	void Pressed(float delta, const SDL_Event& sdlEvent, Sprite* spriteAnim, const Uint8* keysPressed) {
		// Key Pressed
		if (keysPressed[SDL_SCANCODE_W])
		{

		}
		if (keysPressed[SDL_SCANCODE_S])
		{

		}
		if (keysPressed[SDL_SCANCODE_A])
		{
			Player->Velocity.X = Calculator::MoveTowards(Player->Velocity.X, -Player->Stat->Speed, Player->Stat->Acceleration);
			spriteAnim->Play("walk");
			spriteAnim->RenderFlip = SDL_FLIP_HORIZONTAL;
			//Ent->Position.X += Ent->Velocity.X;
		}
		if (keysPressed[SDL_SCANCODE_D])
		{
			Player->Velocity.X = Calculator::MoveTowards(Player->Velocity.X, Player->Stat->Speed, Player->Stat->Acceleration);
			spriteAnim->Play("walk");
			spriteAnim->RenderFlip = SDL_FLIP_NONE;
			//Ent->Position.X += Ent->Velocity.X;
		}


		// Key Released
		if (!keysPressed[SDL_SCANCODE_W])
		{

		}
		if (!keysPressed[SDL_SCANCODE_S])
		{

		}
		if (!keysPressed[SDL_SCANCODE_A] && !keysPressed[SDL_SCANCODE_D])
		{
			Player->Velocity.X = Calculator::MoveTowards(Player->Velocity.X, 0, Player->Stat->Deceleration);
			spriteAnim->Play("idle");
		}
	}

	void JustPressed(float delta, const SDL_Event& sdlEvent, Sprite* spriteAnim, const Uint8* keysPressed) {
		if (Player->IsGrounded && keysPressed[SDL_SCANCODE_SPACE] && !PostKeysPressed[SDL_SCANCODE_SPACE])
		{
			// Jump
			Player->Velocity.Y = Player->Stat->JumpSpeed;
			Player->IsGrounded = false;
		}

		if (!Player->IsGrounded && Player->Velocity.Y < 0 && !keysPressed[SDL_SCANCODE_SPACE] && PostKeysPressed[SDL_SCANCODE_SPACE])
		{
			Player->Velocity.Y = Player->Velocity.Y / 2.f;
		}
	}

private:
	Uint8 PostKeysPressed[SDL_NUM_SCANCODES]{ 0 };
	Player* Player;
	//Collider& Collider;
};