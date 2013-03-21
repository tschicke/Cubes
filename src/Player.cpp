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

Player::Player() {
	yaw = 0;
	pitch = 0;
}

Player::~Player() {
}

void Player::input() {
	int x = 0, y = 0, z = 0;
	if (ts::Keyboard::isKeyPressed(ts::Keyboard::A)) {
		x += -1;
	}
	if (ts::Keyboard::isKeyPressed(ts::Keyboard::D)) {
		x += 1;
	}

	if (ts::Keyboard::isKeyPressed(ts::Keyboard::W)) {
		z += -1;
	}
	if (ts::Keyboard::isKeyPressed(ts::Keyboard::S)) {
		z += 1;
	}

	moveVector = camera.getMoveVector(x, y, z);
}

void Player::update(time_t dt) {
	//TODO check collisions
	//TODO make world class

	position += moveVector;

	moveVector = ts::vec3();//Reset move vector every frame;
}

ts::vec3 Player::getPosition() {
	return position;
}

void Player::setPosition(ts::vec3 newPos) {
	position = newPos;
}
