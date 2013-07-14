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
	loaded = false;
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

		int v0, v1, v2, v3, v4, v5, v6, v7;

		Renderer& renderer = Renderer::getMainRenderer();
		renderer.createMesh(&playerModelID);

		v0 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), 0, 0, 0);
		v1 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), 0, 0, 0);
		v2 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 1, 0), glm::vec3(0, 0, 1), 0, 0, 0);
		v3 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), 0, 0, 0);
		v4 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), 0, 0, 0);
		v5 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 0, 1), glm::vec3(0, 0, 1), 0, 0, 0);
		v6 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 1, 1), glm::vec3(0, 0, 1), 0, 0, 0);
		v7 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 1, 1), glm::vec3(0, 0, 1), 0, 0, 0);

		renderer.addLineToMesh(playerModelID, v0, v1);
		renderer.addLineToMesh(playerModelID, v1, v2);
		renderer.addLineToMesh(playerModelID, v2, v3);
		renderer.addLineToMesh(playerModelID, v3, v0);

		renderer.addLineToMesh(playerModelID, v4, v5);
		renderer.addLineToMesh(playerModelID, v5, v6);
		renderer.addLineToMesh(playerModelID, v6, v7);
		renderer.addLineToMesh(playerModelID, v7, v4);

		renderer.addLineToMesh(playerModelID, v0, v4);
		renderer.addLineToMesh(playerModelID, v1, v5);
		renderer.addLineToMesh(playerModelID, v2, v6);
		renderer.addLineToMesh(playerModelID, v3, v7);

//		renderer.createPrism(playerModelID, glm::vec3(0.f, 0.f, 0.f), 1.f, 1.f, 1.f);

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
		Entity * entity = new DynamicEntity(parentWorld, camera.getPosition(), (camera.getLook() - camera.getPosition()) * 0.2f);
		parentWorld->addEntity(entity);
	}

	int mouseDX, mouseDY;
	mouseDX = ts::Mouse::getLastMove().x;
	mouseDY = ts::Mouse::getLastMove().y;
	camera.rotateWithMove(mouseDX, mouseDY);
}

void Player::gravity() {
	velocity.y -= gravityStrength;
}

void Player::jump() {
	if (onGround) {
		velocity.y += jumpStrength;
	}
}

//void Player::checkCollisions() {
//	glm::vec3 nextPosition = position + moveVector + velocity;
//
//	//X checks
//	if (nextPosition.x != position.x) {
//		for (int c = 0; c < 12; ++c) {
//			float xt = (nextPosition.x + (c % 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));
//			float yt = (position.y + (c / 4 * (PLAYER_HEIGHT / 2)));
//			float zt = (position.z + ((c % 4) / 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));	// - (c / 2 * -0.01) is temp
//
//			Block * nextBlockX = parentWorld->getBlockAt(floorf(xt), floorf(yt), floorf(zt));
//			if (nextBlockX != NULL && nextBlockX->isSolid()) {
//				moveVector.x = roundf(xt) - (position.x + (c % 2 * (PLAYER_WIDTH + 0.001f)) - ((PLAYER_WIDTH + 0.001f) / 2));
//				velocity.x = 0;
//				break;
//			}
//		}
//	}
//
//	nextPosition = position + moveVector + velocity;
//
//	//Z checks
//	if (nextPosition.z != position.z) {
//		for (int c = 0; c < 12; ++c) {
//			float zt = (nextPosition.z + (c % 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));
//			float yt = (position.y + (c / 4 * (PLAYER_HEIGHT / 2)));
//			float xt = (nextPosition.x + ((c % 4) / 2 * (PLAYER_WIDTH)) - (PLAYER_WIDTH / 2));	// - (c / 2 * -0.01) is temp
//
//			Block * nextBlockZ = parentWorld->getBlockAt(floorf(xt), floorf(yt), floorf(zt));
//			if (nextBlockZ != NULL && nextBlockZ->isSolid()) {
//				moveVector.z = roundf(zt) - (position.z + (c % 2 * (PLAYER_WIDTH + 0.001f)) - ((PLAYER_WIDTH + 0.001f) / 2));
//				velocity.z = 0;
//				break;
//			}
//		}
//	}
//
//	nextPosition = position + moveVector + velocity;
//
//	//Y checks
//	if (nextPosition.y != position.y) {
//		for (int c = 0; c < 8; ++c) {
//			float zt = (nextPosition.z + (c % 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));
//			float yt = (nextPosition.y + (c / 4 * PLAYER_HEIGHT));
//			float xt = (nextPosition.x + ((c % 4) / 2 * PLAYER_WIDTH) - (PLAYER_WIDTH / 2));	// - (c / 2 * -0.01) is temp
//
//			Block * nextBlockY = parentWorld->getBlockAt(floorf(xt), floorf(yt), floorf(zt));
//			if (nextBlockY != NULL && nextBlockY->isSolid()) {
//				velocity.y = 0;
//				moveVector.y = roundf(yt) - (position.y + (c / 4 * (PLAYER_HEIGHT + 0.001f)));
//				//-(position.y - (floorf(yt) + 1));
//				if (nextPosition.y < position.y) {
//					onGround = true;
//				}
//				break;
//			} else {
//				onGround = false;
//			}
//		}
//	}
//
//	//Temp "falling off map" fix
//	if (position.y < -64) {
//		move(glm::vec3(0, 96, 0));
//		velocity.y = 0;
//	}
//}

void Player::update(time_t dt) {
	//if(needsRaytrace)
	glm::vec3 startVec = camera.getPosition();
	glm::vec3 endVec = startVec + ((camera.getLook() - startVec) * 4.f); //12 = block break range
	selectedBlock = parentWorld->raytraceBlocks(startVec, endVec);

	input();
	gravity();
//	std::cout << "move vec = " << moveVector.x << ' ' << moveVector.y << ' ' << moveVector.z << '\n';
 	checkCollisions(); //Check collisions last, after movevector and velocity have been completely changed
// 	std::cout << "move vec = " << moveVector.x << ' ' << moveVector.y << ' ' << moveVector.z << '\n' << '\n';

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
	shaderProgram.useProgram();

	glm::mat4 modelMatrix = glm::translate((float) selectedBlock.x, (float) selectedBlock.y, (float) selectedBlock.z);	// * glm::rotate(yaw, 0.f, 1.f, 0.f);

	shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
	shaderProgram.setUniform("viewMatrix", parentWorld->getMainPlayer()->getCameraViewMatrix(), 1);
	shaderProgram.setUniform("projectionMatrix", Renderer::getProjectionMatrix(), 1);

	Renderer::getMainRenderer().renderMesh(playerModelID);

	glUseProgram(0);
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
