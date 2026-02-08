#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

class Component {
public:
	Entity* Ent;
public:
	virtual bool Init() {
		return false;
	}
	virtual void Update(float delta) {

	}
	virtual void PhysicsUpdate(float delta) {

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
	void Update(float delta) {
		for (std::unique_ptr<Component>& item : Components)
		{
			item->Update(delta);
		}
	}

	void PhysicsUpdate(float delta) {
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

	void Update(float delta) {
		for (auto& e : Entities)
		{
			e->Update(delta);
		}
	}

	void PhysicsUpdate(float delta) {
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

	void Refresh() {
		Entities.erase(std::remove_if(std::begin(Entities), std::end(Entities), [](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsActive();
			}),
			std::end(Entities));
	}

	Entity& AddEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		Entities.emplace_back(std::move(uPtr));
		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> Entities;
};
