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

		MousePress(delta, sdlEvent, spriteAnim);
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
	void MousePress(float delta, const SDL_Event& sdlEvent, Sprite* spriteAnim) {
		int mouseX, mouseY;
		Uint8 mouseActions = SDL_GetMouseState(&mouseX, &mouseY);
		MousePosition = Vector2(mouseX, mouseY);

		if (mouseActions & SDL_BUTTON_LMASK)
		{
			std::cout << "Left button clicked at: " << MousePosition << std::endl;
		}
		if (mouseActions & SDL_BUTTON_RMASK)
		{
			std::cout << "Right button clicked at: " << MousePosition << std::endl;
		}
		if (mouseActions & SDL_BUTTON_MMASK)
		{
			std::cout << "Middle button clicked at: " << MousePosition << std::endl;
		}
	}

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

		if (keysPressed[SDL_SCANCODE_E] && !PostKeysPressed[SDL_SCANCODE_E])
		{
			// Quick Heal
			std::cout << "Grappling pressed" << std::endl;
		}

		if (keysPressed[SDL_SCANCODE_Q] && !PostKeysPressed[SDL_SCANCODE_Q])
		{
			// Quick Heal
			std::cout << "Quick heal pressed" << std::endl;
		}

		if (keysPressed[SDL_SCANCODE_M] && !PostKeysPressed[SDL_SCANCODE_M])
		{
			// Quick Heal
			std::cout << "Map pressed" << std::endl;
		}

		if (!Player->IsGrounded && Player->Velocity.Y < 0 && !keysPressed[SDL_SCANCODE_SPACE] && PostKeysPressed[SDL_SCANCODE_SPACE])
		{
			Player->Velocity.Y = Player->Velocity.Y / 2.f;
		}
	}

private:
	Vector2 MousePosition = Vector2();

	Uint8 PostKeysPressed[SDL_NUM_SCANCODES]{ 0 };
	Player* Player;
	//Collider& Collider;
};