/*
 * Player.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "Player.h"
#include "GameLayer.h"
#include "Keyboard.h"

using namespace glm;

Player::Player() {
	yaw = 0;
	pitch = 0;
}

Player::~Player() {
}

void Player::input() {
	int x = 0, y = 0, z = 0;
	if (ts::Keyboard::isKeyPressed(ts::Keyboard::A)) {

	}
}

void Player::update(time_t dt) {
	//TODO check collisions

	position += moveVector;

	moveVector = ts::vec3<float>();
}

ts::vec3<float> Player::getPosition() {
	return position;
}

void Player::setPosition(ts::vec3<float> newPos) {
	position = newPos;
}
