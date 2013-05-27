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

#include "Keyboard.h"
#include "Mouse.h"

#include <math.h>//Temp?
Player::Player() {
	yaw = 0;
	pitch = 0;
	moveSpeed = 0.0f;
	world = NULL;
	gravityStrength = 0.f;
	jumpStrength = 0.f;
	gravityVel = 0;
	onGround = false;
	loaded = false;
}

Player::Player(ts::World * world) {
	init(world);
}

Player::~Player() {
}

void Player::init(ts::World * world) {
	yaw = 270;
	pitch = 0;
	moveSpeed = 0.3f;
	this->world = world;
	gravityStrength = 0.01f;
	jumpStrength = 0.3f;
	gravityVel = 0;
	onGround = false;
	camera.setPosition(glm::vec3(position.x, position.y + CAMERA_HEIGHT, position.z));
	loadPlayerModel();
}

void Player::loadPlayerModel() {
	if (!loaded) {
		Shader vertexShader;
		vertexShader.loadShader("shaders/colorShader.vert", GL_VERTEX_SHADER);

		Shader fragmentShader;
		fragmentShader.loadShader("shaders/colorShader.frag", GL_FRAGMENT_SHADER);

		shaderProgram.createProgram();
		shaderProgram.addShader(&vertexShader);
		shaderProgram.addShader(&fragmentShader);
		shaderProgram.linkProgram();

		vertexShader.deleteShader();
		fragmentShader.deleteShader();

		playerModelID.setColorType(ColorType_Color);

		Renderer& renderer = Renderer::getMainRenderer();
		renderer.createMesh(&playerModelID);

		renderer.createPrism(playerModelID, glm::vec3(-0.375f, 0.f, -0.375f), 0.75f, 0.5f, 0.75f);

		renderer.endMesh(&playerModelID);

		loaded = true;
	}
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

	if(ts::Keyboard::checkKeyEvent(ts::Keyboard::R) == ts::Keyboard::keyPressed){
		int floorX = floorf(position.x);
		int floorY = floorf(position.y);
		int floorZ = floorf(position.z);
//
		for (int x = floorX - 6; x < floorX + 7; ++x) {
			for (int y = floorY - 6; y < floorY + 7; ++y) {
				for (int z = floorZ - 6; z < floorZ + 7; ++z) {
					Chunk * chunk = world->getChunkAt(x, y, z);
					if (chunk != NULL) {
						Block * block = chunk->getBlockAtCoordinate(x, y, z);
						if (block != NULL && !(block->getBlockType() == blockType_Air)) {
							chunk->removeBlockAtPosition(x, y, z);
						}
					}
				}
			}
		}
	}

	int mouseDX, mouseDY;
	mouseDX = ts::Mouse::getLastMove().x;
	mouseDY = ts::Mouse::getLastMove().y;
	camera.rotateWithMove(mouseDX, mouseDY);
}

void Player::gravity() {
//	if (!onGround) {
	velocity.y -= gravityStrength;
//	}
}

void Player::jump() {
	if (onGround) {
		velocity.y += jumpStrength;
	}
}
void Player::checkCollisions() {
	glm::vec3 nextPosition = position + moveVector + velocity;

	//TODO fix corner collisions
	//TODO fix false positive collisions due to overlap in corner and next block

	//X checks
	if (nextPosition.x != position.x) {
		for (int c = 0; c < 4; ++c) {
			float xt = (nextPosition.x + (c % 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));
			float zt = (position.z + (c / 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));	// - (c / 2 * -0.01) is temp

			Block * nextBlockX = world->getBlockAt(floorf(xt), floorf(position.y), floorf(zt));
			if (nextBlockX != NULL && nextBlockX->isSolid()) {
				moveVector.x = roundf(xt) - (position.x + (c % 2 * (PLAYER_WIDTH + 0.01)) - ((PLAYER_WIDTH + 0.01) / 2));
				velocity.x = 0;
				break;
			}
		}
	}

	//Z checks
	if (nextPosition.z != position.z) {
		for (int c = 0; c < 4; ++c) {
			float zt = (nextPosition.z + (c % 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));
			float xt = (position.x + (c / 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));	// - (c / 2 * -0.01) is temp

			Block * nextBlockZ = world->getBlockAt(floorf(xt), floorf(position.y), floorf(zt));
			if (nextBlockZ != NULL && nextBlockZ->isSolid()) {
				moveVector.z = roundf(zt) - (position.z + (c % 2 * (PLAYER_WIDTH + 0.01)) - ((PLAYER_WIDTH + 0.01) / 2));
				velocity.z = 0;
				break;
			}
		}
	}

	//Y checks
	for (int c = 0; c < 4; ++c) {
		float zt = (position.z + (c % 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));
		float xt = (position.x + (c / 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));	// - (c / 2 * -0.01) is temp

		Block * nextBlockY = world->getBlockAt(floorf(xt), floorf(nextPosition.y), floorf(zt));
		if (nextBlockY != NULL && nextBlockY->isSolid()) {
			moveVector.y = -(position.y - (floorf(nextPosition.y) + 1));
			velocity.y = 0;
//		gravityVel = 0;
			onGround = true;
			break;
		} else {
			onGround = false;
		}
	}

	//Temp "falling off map" fix
	if (position.y < -64) {
		move(glm::vec3(0, 96, 0));
		velocity.y = 0;
	}
}

void Player::update(time_t dt) {
	input();
	gravity();
	checkCollisions(); //Check collisions last, after movevector and velocity have been completely changed

	moveVector += velocity;

	move(moveVector);

	moveVector = glm::vec3();	//Reset move vector every frame;
}

void Player::draw(glm::mat4 * viewMat) {
//	shaderProgram.useProgram();

//	glm::mat4 modelMatrix = glm::translate(position.x, position.y, position.z);	// * glm::rotate(yaw, 0.f, 1.f, 0.f);

//	shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
//	shaderProgram.setUniform("viewMatrix", viewMat, 1);
//	shaderProgram.setUniform("projectionMatrix", Renderer::getProjectionMatrix(), 1);

//	Renderer::getMainRenderer().renderMesh(playerModelID);
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
	move(moveVector);
}

glm::mat4 * Player::getCameraViewMatrix() {
	return camera.getViewMatrix();
}
