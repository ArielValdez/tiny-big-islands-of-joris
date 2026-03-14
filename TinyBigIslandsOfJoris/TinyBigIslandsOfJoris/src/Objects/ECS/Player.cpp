#include "Player.hpp"
#include "../EntityComponentSystem.hpp"
#include "../Inventory/Inventory.hpp"

Player::Player(Manager& manager) : Entity(manager) {
	Stat = new Stats();
	DefaultStat = Stats();
	Pocket = new Inventory(50);
}

Player::~Player() {
	Stat = nullptr;
}