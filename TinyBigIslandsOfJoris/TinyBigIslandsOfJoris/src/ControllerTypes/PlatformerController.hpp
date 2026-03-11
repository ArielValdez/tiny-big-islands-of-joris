#pragma once
#include <SDL.h>
#include "Controller.hpp"

class PlatformerController : public Controller {
public:
	PlatformerController() {

	}

	bool Init(Player* player) override {
		PlayerEntity = player;
		return true;
	}

	void Update(double delta, const SDL_Event& sdlEvent, Sprite* spriteAnim, const Uint8* action) override {
		// Gravity
		PlayerEntity->Velocity.Y = Calculator::MoveTowards(PlayerEntity->Velocity.Y, Game::Gravity.Y, PlayerEntity->Stat->FallSpeed);

		JustPressed(delta, sdlEvent, spriteAnim, action);
		Pressed(delta, sdlEvent, spriteAnim, action);

		SDL_memcpy(PostKeysPressed, action, SDL_NUM_SCANCODES);
	}

	void PostUpdate(double delta) override {
		//std::cout << Player->Velocity << std::endl;
		//Player->Position.X += Player->Velocity.X;
	}

	~PlatformerController() {

	}

private:
	void Pressed(float delta, const SDL_Event& sdlEvent, Sprite* spriteAnim, const Uint8* keysPressed) {
		// Key Pressed
#if DEBUG
		if (keysPressed[SDL_SCANCODE_F8])
		{
			Game::IsRunning = false;
		}
#endif
		if (keysPressed[SDL_SCANCODE_W])
		{

		}
		if (keysPressed[SDL_SCANCODE_S])
		{

		}
		if (keysPressed[SDL_SCANCODE_A])
		{
			PlayerEntity->Velocity.X = Calculator::MoveTowards(PlayerEntity->Velocity.X, -PlayerEntity->Stat->Speed, PlayerEntity->Stat->Acceleration);
			spriteAnim->Play("walk");
			spriteAnim->RenderFlip = SDL_FLIP_HORIZONTAL;
			//Ent->Position.X += Ent->Velocity.X;
		}
		if (keysPressed[SDL_SCANCODE_D])
		{
			PlayerEntity->Velocity.X = Calculator::MoveTowards(PlayerEntity->Velocity.X, PlayerEntity->Stat->Speed, PlayerEntity->Stat->Acceleration);
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
			PlayerEntity->Velocity.X = Calculator::MoveTowards(PlayerEntity->Velocity.X, 0, PlayerEntity->Stat->Deceleration);
			spriteAnim->Play("idle");
		}
	}

	void JustPressed(float delta, const SDL_Event& sdlEvent, Sprite* spriteAnim, const Uint8* keysPressed) {
		if (PlayerEntity->IsGrounded && keysPressed[SDL_SCANCODE_SPACE] && !PostKeysPressed[SDL_SCANCODE_SPACE])
		{
			// Jump
			PlayerEntity->Velocity.Y = PlayerEntity->Stat->JumpSpeed;
			PlayerEntity->IsGrounded = false;
		}

		if (keysPressed[SDL_SCANCODE_ESCAPE] && !PostKeysPressed[SDL_SCANCODE_ESCAPE])
		{
			// Inventory
			std::cout << "Inventory pressed" << std::endl;
		}

		if (keysPressed[SDL_SCANCODE_E] && !PostKeysPressed[SDL_SCANCODE_E])
		{
			// Grappling
			std::cout << "Grappling pressed" << std::endl;
		}

		if (keysPressed[SDL_SCANCODE_Q] && !PostKeysPressed[SDL_SCANCODE_Q])
		{
			// Quick Heal
			std::cout << "Quick heal pressed" << std::endl;
		}

		if (keysPressed[SDL_SCANCODE_M] && !PostKeysPressed[SDL_SCANCODE_M])
		{
			// Map
			std::cout << "Map pressed" << std::endl;
		}

		if (!PlayerEntity->IsGrounded && PlayerEntity->Velocity.Y < 0 && !keysPressed[SDL_SCANCODE_SPACE] && PostKeysPressed[SDL_SCANCODE_SPACE])
		{
			PlayerEntity->Velocity.Y = PlayerEntity->Velocity.Y / 2.f;
		}
	}

private:
	Uint8 PostKeysPressed[SDL_NUM_SCANCODES]{ 0 };

	//Collider& Collider;
};