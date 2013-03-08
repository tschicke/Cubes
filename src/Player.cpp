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

	movementStates[forward] = false;
	movementStates[back] = false;
	movementStates[right] = false;
	movementStates[left] = false;
	movementStates[up] = false;
	movementStates[down] = false;
}

Player::~Player() {
}

void Player::update(){//Add shouldUpdate?
	move();
	mainCamera.update();
}

vec3 Player::getPosition(){
	return position;
}

void Player::setPosition(vec3 newPos){
	position = newPos;
}

void Player::setYaw(int newYaw){
	yaw = newYaw;
}

void Player::move(){//Clean player, gamelayer, and gamescene classes up
	float x = 0, y = 0, z = 0;
	if(movementStates[forward] && !movementStates[back])z = -moveSpeed;
	if(movementStates[back] && !movementStates[forward])z = moveSpeed;
	if(movementStates[left] && !movementStates[right])x = moveSpeed;
	if(movementStates[right] && !movementStates[left])x = -moveSpeed;
	if(movementStates[up] && !movementStates[down])y = moveSpeed;
	if(movementStates[down] && !movementStates[up])y = -moveSpeed;
	mainCamera.move(x, y, z);
	setPosition(mainCamera.getPosition());
}

void Player::look(int dx, int dy){
	mainCamera.look(dx, dy);
	setYaw(mainCamera.getYaw());
}

FirstPersonCamera* Player::getMainCamera(){
	return &mainCamera;
}

void Player::setMovementState(int state, bool value){
	movementStates[state] = value;
}

