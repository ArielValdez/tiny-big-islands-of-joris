#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "Vector2.hpp"
#include "SDL.h"

class Component;
class Entity;

class Component {
public:
	Entity* Ent;
public:
	virtual bool Init() {
		return false;
	}
	virtual void Update(double delta) {

	}
	virtual void PhysicsUpdate(double delta) {

	}
	virtual void HandlerEvent(const SDL_Event& sdlEvent) {

	}
	virtual void Draw() {

	}
	virtual ~Component() {

	}
};

constexpr std::size_t MaxComponents = 32;

using ComponentID = std::size_t;
using ComponentBitSet = std::bitset<MaxComponents>;
using ComponentArray = std::array<Component*, MaxComponents>;

inline ComponentID GetComponentId() {
	static ComponentID id = 0;
	return id++;
}

template <typename T> inline ComponentID GetComponentId() noexcept {
	static ComponentID typeId = GetComponentId();
	return typeId;
}

class Entity {
public:
	Vector2 Position = Vector2(0, 0);
	Vector2 Velocity = Vector2(0, 0);
public:
	void Update(double delta) {
		for (std::unique_ptr<Component>& item : Components)
		{
			item->Update(delta);
		}
	}

	void PhysicsUpdate(double delta) {
		for (std::unique_ptr<Component>& item : Components) {
			item->PhysicsUpdate(delta);
		}
	}

	void Draw() {
		// render
		for (std::unique_ptr<Component>& item : Components) {
			item->Draw();
		}
	}

	void HandleEvents(SDL_Event sdlEvent) {
		for (std::unique_ptr<Component>& item : Components) {
			item->HandlerEvent(sdlEvent);
		}
	}

	bool IsActive() const { return Active; }

	void Destroy() {
		Active = false;
	}

	template <typename T> bool HasComponent() const {
		return CompBitSet[GetComponentId<T>];
	}

	template <typename T, typename... TArgs> T& AddComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->Ent = this;
		std::unique_ptr<Component> uPtr{ c };
		Components.emplace_back(std::move(uPtr));

		CompArray[GetComponentId<T>()] = c;
		CompBitSet[GetComponentId<T>()] = true;

		c->Init();

		return *c;
	}

	template <typename T> T& GetComponent() const {
		auto ptr(CompArray[GetComponentId<T>()]);
		return *static_cast <T*>(ptr);
	}

private:
	bool Active = true;
	std::vector<std::unique_ptr<Component>> Components;
	ComponentArray CompArray;
	ComponentBitSet CompBitSet;
};

class Manager {
public:

public:
	void Init() {
		// Init entities
	}

	void Update(double delta) {
		for (auto& e : Entities)
		{
			e->Update(delta);
		}
	}

	void PhysicsUpdate(double delta) {
		for (auto& e : Entities)
		{
			e->PhysicsUpdate(delta);
		}
	}

	void Draw() {
		for (auto& e : Entities)
		{
			e->Draw();
		}
	}

	void HandleEvents(SDL_Event sdlEvent) {
		for (auto& e : Entities)
		{
			e->HandleEvents(sdlEvent);
		}
	}

	void Refresh() {
		Entities.erase(std::remove_if(std::begin(Entities), std::end(Entities), [](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsActive();
			}),
			std::end(Entities));
	}

	void Destroy() {
		for (auto& e : Entities)
		{
			e->Destroy();
		}
		Refresh();
	}

	Entity& AddEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		Entities.emplace_back(std::move(uPtr));
		return *e;
	}

	template <typename T> Entity& AddEntity() {
		Entity* e = new T();
		std::unique_ptr<Entity> uPtr{ e };
		Entities.emplace_back(std::move(uPtr));
		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> Entities;
};
