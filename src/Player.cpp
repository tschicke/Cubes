/*
 * Player.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: Tyler
 */

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Player.h"

#include "World.h"

#include "Arrow.h"

#include "Keyboard.h"
#include "Mouse.h"

#include "SelectedBlock.h"

#include <math.h>//Temp?
Player::Player() {
	yaw = 0;
	pitch = 0;
	moveSpeed = 0.0f;
	parentWorld = NULL;
	gravityStrength = 0.f;
	jumpStrength = 0.f;
	onGround = false;
	activeBlock = blockType_Null;
}

Player::Player(ts::World * parentWorld) {
	init(parentWorld);
}

Player::~Player() {
}

void Player::init(ts::World * parentWorld) {
	DynamicEntity::init(parentWorld, glm::vec3(), glm::vec3());
	yaw = 270;
	pitch = 0;
	moveSpeed = 0.2f;
	gravityStrength = 0.01f;
	jumpStrength = 0.3f;
	onGround = false;
	activeBlock = blockType_Grass;
	camera.setPosition(glm::vec3(position.x, position.y + CAMERA_HEIGHT, position.z));
	halfDimentions = glm::vec3(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2, PLAYER_WIDTH / 2);
	selectedBlock.init(0, 0, 0, NULL, face_nocollision, this);
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

	if (ts::Keyboard::isKeyPressed(ts::Keyboard::Q)) {
		y += moveSpeed;
	}
	if (ts::Keyboard::isKeyPressed(ts::Keyboard::E)) {
		y += -moveSpeed;
	}

	moveVector = camera.getMoveVector(x, y, z);

	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Space) == ts::Keyboard::keyPressed) {
		jump();
	}

	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::R) == ts::Keyboard::keyPressed) {
		int floorX = floorf(position.x);
		int floorY = floorf(position.y);
		int floorZ = floorf(position.z);

		for (int x = floorX - 6; x < floorX + 7; ++x) {
			for (int y = floorY - 6; y < floorY + 7; ++y) {
				for (int z = floorZ - 6; z < floorZ + 7; ++z) {
					parentWorld->setBlockTypeAtPosition(x, y, z, blockType_Air);
				}
			}
		}
	}

	if (ts::Mouse::checkMouseButtonEvent(ts::Mouse::Button0) == ts::Mouse::buttonPressed) {
		parentWorld->setBlockTypeAtPosition(selectedBlock.x, selectedBlock.y, selectedBlock.z, blockType_Air);
	}

	if (ts::Mouse::checkMouseButtonEvent(ts::Mouse::Button1) == ts::Mouse::buttonPressed) {
		glm::vec3 addBlockPosition = selectedBlock.getAddBlockPosition();
		parentWorld->setBlockTypeAtPosition(addBlockPosition.x, addBlockPosition.y, addBlockPosition.z, activeBlock);
	}

	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Num1) == ts::Keyboard::keyPressed) {
		activeBlock = blockType_Grass;
	} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Num2) == ts::Keyboard::keyPressed) {
		activeBlock = blockType_Dirt;
	} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Num3) == ts::Keyboard::keyPressed) {
		activeBlock = blockType_Stone;
	} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Num4) == ts::Keyboard::keyPressed) {
		activeBlock = blockType_Tree;
	} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Num5) == ts::Keyboard::keyPressed) {
		activeBlock = blockType_Brick;
	}

	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::P) == ts::Keyboard::keyPressed) {
		Entity * entity = new Arrow(parentWorld, camera.getPosition(), (camera.getLook() - camera.getPosition()) * 0.2f);
		entity->setYaw(-camera.getYaw() - 90);
		entity->setPitch(camera.getPitch());
		parentWorld->addEntity(entity);
	}

	int mouseDX, mouseDY;
	mouseDX = ts::Mouse::getLastMove().x;
	mouseDY = ts::Mouse::getLastMove().y;
	camera.rotateWithMove(mouseDX, mouseDY);
	setYaw(-camera.getYaw() - 90);
}

void Player::gravity() {
	velocity.y -= gravityStrength;
}

void Player::jump() {
	if (onGround) {
		velocity.y += jumpStrength;
	}
}

void Player::update(time_t dt) {
	//if(needsRaytrace)
	glm::vec3 startVec = camera.getPosition();
	glm::vec3 endVec = startVec + ((camera.getLook() - startVec) * 4.f); //12 = block break range
	parentWorld->raytraceBlocks(startVec, endVec, &selectedBlock);

	input();
	gravity();
 	checkCollisions(); //Check collisions last, after movevector and velocity have been completely changed

 	//TODO use DynamicEntity::update() or Character::update();

	if(floorColl){
		onGround = true;
	} else {
		onGround = false;
	}

	moveVector += velocity;

	move(moveVector);

	moveVector = glm::vec3();	//Reset move vector every frame;
}

void Player::draw() {
	model.render();
	selectedBlock.render();
}

void Player::setPosition(glm::vec3 newPos) {
	glm::vec3 moveVector = newPos - position;
	move(moveVector);
}

void Player::move(glm::vec3 moveVector) {
	DynamicEntity::move(moveVector);
	camera.move(moveVector);
}

const char* Player::getModelPath() {
	return "models/Human.model";
}

void Player::move(float x, float y, float z) {
	glm::vec3 moveVector(x, y, z);
	move(moveVector);
}

glm::mat4 * Player::getCameraViewMatrix() {
	return camera.getViewMatrix();
}
