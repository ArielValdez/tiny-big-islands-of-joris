#include "EntityComponentSystem.hpp"

void Entity::AddGroup(Group group) {
	GroupingBitSet[group] = true;
	Man.AddToGroup(this, group);
}