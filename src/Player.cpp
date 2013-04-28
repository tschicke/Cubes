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

Player::Player() {
	yaw = 0;
	pitch = 0;
	moveSpeed = 0.0f;
	world = NULL;
	gravityStrength = 0.f;
	jumpStrength = 0.f;
	gravityVel = 0;
	onGround = false;
}

Player::Player(ts::World * world) {
	init(world);
}

Player::~Player() {
}

void Player::init(ts::World * world) {
	yaw = 0;
	pitch = 0;
	moveSpeed = 0.3f;
	this->world = world;
	gravityStrength = 0.01f;
	jumpStrength = 0.3f;
	gravityVel = 0;
	onGround = false;
	camera.setPosition(glm::vec3(position.x, position.y + CAMERA_HEIGHT, position.z));
	loadPlayerModel(); //TODO add loaded bool
}

void Player::loadPlayerModel() {
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

	playerModelID.setColorType(Color);

	Renderer& renderer = Renderer::getMainRenderer();
	renderer.createMesh(&playerModelID);

	renderer.createPrism(playerModelID, glm::vec3(-0.375f, 0.f, -0.375f), 0.75f, 0.5f, 0.75f);

	renderer.endMesh(&playerModelID);
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
	glm::vec3 nextPosition = position + moveVector + velocity; // add if nextposition.x, y, or z != position.x, y, or z checks

	//X checks
//	Chunk * nextChunkX = world->getChunkAt(nextPosition.x + (PLAYER_WIDTH / 2), position.y, position.z);
//	Block * nextBlockX = (nextChunkX ? nextChunkX->getBlockAtCoordinate(nextPosition.x + (PLAYER_WIDTH / 2), position.y, position.z) : NULL);
//	if (nextBlockX && nextBlockX->isDrawn()) {
//		moveVector.x = -(position.x - (int) nextPosition.x - (PLAYER_WIDTH / 2));
//		velocity.x = 0;
//	}
//
//	Chunk * nextChunkXC2 = world->getChunkAt(nextPosition.x - (PLAYER_WIDTH / 2), position.y, position.z);
//	Block * nextBlockXC2 = (nextChunkXC2 ? nextChunkXC2->getBlockAtCoordinate(nextPosition.x - (PLAYER_WIDTH / 2), position.y, position.z) : NULL);
//	if (nextBlockXC2 && nextBlockXC2->isDrawn()) {
//		moveVector.x = -(position.x - (int) nextPosition.x - (PLAYER_WIDTH / 2));
//		velocity.x = 0;
//	}

	if (nextPosition.x != position.x) {
		for (int c = 0; c < 4; ++c) {
			float xt = (nextPosition.x + (c % 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));
			float zt = (position.z + (c / 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));

//			std::cout << "x: " << c << ": (" << xt << ", " << zt << ")\n";

			Chunk * nextChunkX = world->getChunkAt(xt, position.y, zt);
			Block * nextBlockX = (nextChunkX ? nextChunkX->getBlockAtCoordinate(xt, position.y, zt) : NULL);
			if (nextBlockX && nextBlockX->isDrawn()) {
				moveVector.x = (int) xt - position.x - (c % 2 * PLAYER_WIDTH) + (PLAYER_WIDTH / 2);
//				moveVector.x = 0;
				velocity.x = 0;
			}
		}
	}

	//Z checks
//	Chunk * nextChunkZ = world->getChunkAt(position.x, position.y, nextPosition.z + (PLAYER_WIDTH / 2));
//	Block * nextBlockZ = (nextChunkZ ? nextChunkZ->getBlockAtCoordinate(position.x, position.y, nextPosition.z + (PLAYER_WIDTH / 2)) : NULL);
//	if (nextBlockZ && nextBlockZ->isDrawn()) {
//		moveVector.z = -(position.z - (int) nextPosition.z - (PLAYER_WIDTH / 2));
//		velocity.z = 0;
//	}
//
//	Chunk * nextChunkZC2 = world->getChunkAt(position.x, position.y, nextPosition.z - (PLAYER_WIDTH / 2));
//	Block * nextBlockZC2 = (nextChunkZC2 ? nextChunkZC2->getBlockAtCoordinate(position.x, position.y, nextPosition.z - (PLAYER_WIDTH / 2)) : NULL);
//	if (nextBlockZC2 && nextBlockZC2->isDrawn()) {
//		moveVector.z = -(position.z - (int) nextPosition.z - (PLAYER_WIDTH / 2));
//		velocity.z = 0;
//	}

	if (nextPosition.z != position.z) {
		for (int c = 0; c < 4; ++c) {
			float zt = (nextPosition.z + (c % 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));
			float xt = (position.x + (c / 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));

//			std::cout << "z: " << c << ": (" << xt << ", " << zt << ")\n";

			Chunk * nextChunkZ = world->getChunkAt(xt, position.y, zt);
			Block * nextBlockZ = (nextChunkZ ? nextChunkZ->getBlockAtCoordinate(xt, position.y, zt) : NULL);
			if (nextBlockZ && nextBlockZ->isDrawn()) {
				moveVector.z = (int) zt - position.z - (c % 2 * PLAYER_WIDTH) + (PLAYER_WIDTH / 2);
//				std::cout << zt << ", " << (int) zt << ", " << position.z << '\n';
//				std::cout << (int) zt - position.z - (c % 2 * PLAYER_WIDTH) + (PLAYER_WIDTH / 2) << '\n';
//				moveVector.z = 0;
				velocity.z = 0;
			}
		}
	}

	Chunk * nextChunkY = world->getChunkAt(position.x, nextPosition.y, position.z); //TODO add getcubeat function to world?
	Block * nextBlockY = (nextChunkY ? nextChunkY->getBlockAtCoordinate(position.x, nextPosition.y, position.z) : NULL); //TODO change bounds of getblockat(swap inclusive and exclusive)
	if (nextBlockY && nextBlockY->isDrawn()) {
		moveVector.y = -(position.y - ((int) nextPosition.y + 1));
		velocity.y = 0;
//		gravityVel = 0;
		onGround = true;
	} else {
		onGround = false;
	}

	//Temp "falling off map" fix
	if (position.y < 0) {
		move(glm::vec3(0, 32, 0));
		velocity.y = 0;
	}
}

void Player::update(time_t dt) {
	input();
	gravity(); //TODO tweak order of these three function calls
	checkCollisions(); //Check collisions last, after movevector and velocity have been completely changed... should be able to get rid of gravityVel

	moveVector += velocity;

	move(moveVector);

	moveVector = glm::vec3();	//Reset move vector every frame;
}

void Player::draw(glm::mat4 * viewMat) {
	shaderProgram.useProgram();

	glm::mat4 modelMatrix = glm::translate(position.x, position.y, position.z);	// * glm::rotate(yaw, 0.f, 1.f, 0.f);

	shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
	shaderProgram.setUniform("viewMatrix", viewMat, 1);
	shaderProgram.setUniform("projectionMatrix", Renderer::getProjectionMatrix(), 1);

	Renderer::getMainRenderer().renderMesh(playerModelID);
	//FIXME create color shader and rename basicShader to textureShader
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
