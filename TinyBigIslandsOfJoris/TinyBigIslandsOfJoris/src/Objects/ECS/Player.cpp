#include "Player.hpp"
#include "../EntityComponentSystem.hpp"

Player::Player(Manager& manager) : Entity(manager) {
	Stat = new Stats();
}

Player::~Player() {

}