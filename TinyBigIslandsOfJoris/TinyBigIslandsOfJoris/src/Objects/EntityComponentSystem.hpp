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
class Manager;

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
constexpr std::size_t MaxGroups = 32;

using ComponentID = std::size_t;
using Group = std::size_t;
using ComponentBitSet = std::bitset<MaxComponents>;
using GroupBitSet = std::bitset<MaxGroups>;
using ComponentArray = std::array<Component*, MaxComponents>;

inline ComponentID GetComponentId() {
	static ComponentID id = 0u;
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
	Entity(Manager& manager) : Man(manager) {

	}

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

	// Is (in) group?
	bool HasGroup(Group group) {
		return GroupingBitSet[group];
	}

	void AddGroup(Group group);

	void DeleteGroup(Group group) {
		GroupingBitSet[group] = NULL;
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
	Manager& Man;

	bool Active = true;

	std::vector<std::unique_ptr<Component>> Components;

	ComponentArray CompArray;
	ComponentBitSet CompBitSet;
	GroupBitSet GroupingBitSet;
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
		for (size_t i = 0u; i < MaxGroups; i++)
		{
			std::vector<Entity*>& v = GroupedEntities[i];
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* ent) {
						return !ent->IsActive() || !ent->HasGroup(i);
					}
				),
				std::end(v)
			);
		}

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
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		Entities.emplace_back(std::move(uPtr));
		return *e;
	}

	void AddToGroup(Entity* entity, Group group) {
		GroupedEntities[group].emplace_back(entity);
	}

	std::vector<Entity*>& GetGroup(Group group) {
		return GroupedEntities[group];
	}

	template <typename T> Entity& AddEntity() {
		Entity* e = new T(*this);
		std::unique_ptr<Entity> uPtr{ e };
		Entities.emplace_back(std::move(uPtr));
		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> Entities;
	std::array<std::vector<Entity*>, MaxGroups> GroupedEntities;
};
