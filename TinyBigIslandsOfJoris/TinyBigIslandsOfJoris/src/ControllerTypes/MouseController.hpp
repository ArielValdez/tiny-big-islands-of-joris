#pragma once
#include "Controller.hpp"

class MouseController : public Controller {
public:

public:
	bool Init(Player* player) override {
		PlayerEntity = player;
		return true;
	}

	void Update(double delta, const SDL_Event& sdlEvent, Sprite* spriteAnim, const Uint8* action) override {
		int mouseX, mouseY;
		MouseActions = SDL_GetMouseState(&mouseX, &mouseY);
		MousePosition = Vector2(mouseX, mouseY);

		MouseJustPressed(delta, sdlEvent, spriteAnim);
		MousePressed(delta, sdlEvent, spriteAnim);

		SDL_memcpy(&PostMouseButtonPressed, &MouseActions, 6);
	}

	void PostUpdate(double delta) override {
		//std::cout << Player->Velocity << std::endl;
		//Player->Position.X += Player->Velocity.X;
	}

private:
	Uint32 PostMouseButtonPressed;
	Uint32 MouseActions = 0;

	Vector2 MousePosition = Vector2();

private:
	void MouseJustPressed(float delta, const SDL_Event& sdlEvent, Sprite* spriteAnim) {
		/*Vector2 mouseGlobalPosition = MousePosition + Vector2(Game::Camera.x, Game::Camera.y);
		Vector2 tiledMousePosition = TileRenderer::GetTiledPosition(mouseGlobalPosition);*/
		if (MouseActions & SDL_BUTTON_LMASK && !(PostMouseButtonPressed & SDL_BUTTON_LMASK))
		{
			/*std::cout << "Left button clicked at: " << MousePosition << std::endl;
			std::cout << "Mouse global position relative to camera: " << mouseGlobalPosition << std::endl;
			std::cout << "Tile position relative to mouse: " << tiledMousePosition << std::endl;
			Game::AddTile(0, Vector2(0, 0), tiledMousePosition, Vector2(16,16), "Assets/dirt.jpg");*/
		}
	}

	void MousePressed(float delta, const SDL_Event& sdlEvent, Sprite* spriteAnim) {
		/*if (MouseActions & SDL_BUTTON_LMASK)
		{
			std::cout << "Left button clicked at: " << MousePosition << std::endl;
		}*/
		if (MouseActions & SDL_BUTTON_RMASK)
		{
			std::cout << "Right button clicked at: " << MousePosition << std::endl;
		}
		if (MouseActions & SDL_BUTTON_MMASK)
		{
			std::cout << "Middle button clicked at: " << MousePosition << std::endl;
		}
	}

};