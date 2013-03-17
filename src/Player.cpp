/*
 * Player.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "Player.h"

using namespace glm;

Player::Player() {
	yaw = 0;
	mainCamera.setPosition(position);

	moveSpeed = 0.05f;
	lookSpeed = 0.1f;

	movementStates[forward] = false;
	movementStates[back] = false;
	movementStates[right] = false;
	movementStates[left] = false;
	movementStates[up] = false;
	movementStates[down] = false;
	lookDX = 0;
	lookDY = 0;
}

Player::~Player() {
}

void Player::update(time_t dt) { //Add shouldUpdate?
	move();
	look();
	mainCamera.update();
}

vec3 Player::getPosition() {
	return position;
}

void Player::setPosition(vec3 newPos) {
	position = newPos;
}

void Player::setYaw(int newYaw) {
	yaw = newYaw;
}

void Player::move() { //Clean player, gamelayer, and gamescene classes up
	float x = 0, y = 0, z = 0;
	if (movementStates[forward] && !movementStates[back])
		z = -moveSpeed;
	if (movementStates[back] && !movementStates[forward])
		z = moveSpeed;
	if (movementStates[left] && !movementStates[right])
		x = moveSpeed;
	if (movementStates[right] && !movementStates[left])
		x = -moveSpeed;
	if (movementStates[up] && !movementStates[down])
		y = moveSpeed;
	if (movementStates[down] && !movementStates[up])
		y = -moveSpeed;
	if (x || y || z) {
		mainCamera.move(x, y, z);
		setPosition(mainCamera.getPosition());
	}
}

void Player::look() {
	if (lookDX || lookDY) {
		mainCamera.look(lookDX, lookDY);
		setYaw(mainCamera.getYaw());
	}
}

FirstPersonCamera* Player::getMainCamera() {
	return &mainCamera;
}

void Player::setMovementState(MovementState state, bool value) {
	movementStates[state] = value;
}

void Player::setLookStates(int dx, int dy) {
	lookDX = dx;
	lookDY = dy;
}

