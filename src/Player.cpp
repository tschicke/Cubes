/*
 * Player.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "Player.h"
#include "GameLayer.h"

using namespace glm;

Player::Player() :
		gravityStrength(-0.01f) {
	yaw = 0;

	cameraPosition = position;
	cameraPosition.y += height;
	mainCamera.setPosition(cameraPosition);

	moveSpeed = 0.1f;
	jumpStrength = 0.2f;

	movementStates[forward] = false;
	movementStates[back] = false;
	movementStates[right] = false;
	movementStates[left] = false;
	movementStates[up] = false;
	movementStates[down] = false;
	lookDX = 0;
	lookDY = 0;

	height = 2;

	gravityDY = 0;

	inAir = true;

	parentLayer = NULL;
}

Player::~Player() {
}

void Player::setParent(GameLayer * parent) {
	parentLayer = parent;
}

void Player::update(time_t dt) { //Add shouldUpdate?
	updateMoveVec();
	checkCollisions();
	gravity();
	move();
	look();
	mainCamera.update();
}

vec3 Player::getPosition() {
	return position;
}

void Player::setPosition(vec3 newPos) {
	position = newPos;
	cameraPosition = newPos;
	cameraPosition.y += height;
	mainCamera.setPosition(cameraPosition);
}

void Player::setX(float x) {
	glm::vec3 newPlayerPos = position;
	newPlayerPos.x = x;
	setPosition(newPlayerPos);
}

void Player::setY(float y) {
	glm::vec3 newPlayerPos = position;
	newPlayerPos.y = y;
	setPosition(newPlayerPos);
}

void Player::setZ(float z) {
	glm::vec3 newPlayerPos = position;
	newPlayerPos.z = z;
	setPosition(newPlayerPos);
}

void Player::setYaw(int newYaw) {
	yaw = newYaw;
}

void Player::gravity() {
	if (inAir) {
		gravityDY += gravityStrength;
	} //else {
//		gravityDY = 0;
//	}
}

void Player::jump() {
	if (!inAir) {
		gravityDY = jumpStrength;
		inAir = true;
		std::cout << position.x << ", " << position.y << ", " << position.z << "\n";
	}
}

void Player::updateMoveVec() {
	float x = 0, y = 0, z = 0;
	if (movementStates[forward]) {
		z += -moveSpeed;
	}
	if (movementStates[back]) {
		z += moveSpeed;
	}
	if (movementStates[left]) {
		x += moveSpeed;
	}
	if (movementStates[right]) {
		x += -moveSpeed;
	}
	if (movementStates[up]) {
		y += moveSpeed;
	}
	if (movementStates[down]) {
		y += -moveSpeed;
	}
	y += gravityDY;
	if (x || y || z) {
		moveVector = mainCamera.getMoveVector(x, y, z);
		std::cout << moveVector.x << ' ' << moveVector.y << ' ' << moveVector.z << '\n';
	}
}

void Player::checkCollisions() {
	float nextPlayerX = position.x, nextPlayerY = position.y + gravityDY, nextPlayerZ = position.z;

	if (nextPlayerY < 0 && inAir) {
		gravityDY = 0;
		setY(32);
	}

	if (parentLayer != NULL) {
		ChunkManager * manager = parentLayer->getManagerPointer();
		if (manager != NULL) {
			Chunk * chunk = manager->getChunkWithCoordinate(nextPlayerX, nextPlayerY, nextPlayerZ);
			if (chunk != NULL) {
				Block * block = chunk->getBlockAtCoordinate(nextPlayerX, nextPlayerY, nextPlayerZ);
				if (block != NULL && block->isDrawn()) {
					inAir = false;
					gravityDY = 0;
					setY((int) nextPlayerY + Block::cubeSize);
				} else {
					inAir = true;
				}

//				std::cout << block << ", " << (block == NULL ? -1 : block->isDrawn()) << '\n';
			}
//			std::cout << "manager\n";
		}
//		std::cout << "parent\n";
	}
}

void Player::move() { //Clean player, gamelayer, and gamescene classes up
	position += moveVector;
	cameraPosition += moveVector;
	mainCamera.setPosition(cameraPosition);
}

void Player::look() {
//	std::cout << lookDX << ", " << lookDY << '\n';
	if (lookDX || lookDY) {
		mainCamera.look(lookDX, lookDY);
		setYaw(mainCamera.getYaw());
	}
}

FirstPersonCamera * Player::getMainCamera() {
	return &mainCamera;
}

void Player::setMovementState(MovementState state, bool value) {
	movementStates[state] = value;
}

void Player::setLookStates(int dx, int dy) {
	lookDX = dx;
	lookDY = dy;
}

