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
#include "Mouse.h"

Player::Player() {
	yaw = 0;
	pitch = 0;
	moveSpeed = 0.3f;
}

Player::~Player() {
}

void Player::input() {
	float x = 0, y = 0, z = 0;
	if (ts::Keyboard::isKeyPressed(ts::Keyboard::A)) {
		x += -moveSpeed;
	}
	if (ts::Keyboard::isKeyPressed(ts::Keyboard::D)) {
		x += moveSpeed;
	}

	if (ts::Keyboard::isKeyPressed(ts::Keyboard::W)) {
		z += moveSpeed;
	}
	if (ts::Keyboard::isKeyPressed(ts::Keyboard::S)) {
		z += -moveSpeed;
	}

	moveVector = camera.getMoveVector(x, y, z);

	int mouseDX, mouseDY;
	mouseDX = ts::Mouse::getLastMove().x;
	mouseDY = ts::Mouse::getLastMove().y;
	camera.rotateWithMove(mouseDX, mouseDY);
}

void Player::update(time_t dt) {
	//TODO check collisions
	//TODO make world class

	move(moveVector);

	moveVector = glm::vec3();//Reset move vector every frame;
}

glm::vec3 Player::getPosition() {
	return position;
}

void Player::setPosition(glm::vec3 newPos) {
	glm::vec3 moveVector = newPos - position;
	move(moveVector);
}

void Player::move(glm::vec3 moveVector) {
	position += moveVector;
	camera.move(moveVector);
}

void Player::move(float x, float y, float z) {
	glm::vec3 moveVector(x, y, z);
	position += moveVector;
	camera.move(moveVector);
}

glm::mat4 * Player::getCameraViewMatrix(){
	return camera.getViewMatrix();
}
