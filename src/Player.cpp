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
#include "GameLayer.h"

#include "Keyboard.h"
#include "Mouse.h"

Player::Player() {
	yaw = 0;
	pitch = 0;
	moveSpeed = 0.3f;
	loadPlayerModel();
}

Player::~Player() {
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
	std::cout << "player " << playerModelID.getVertexID() << '\n';

	int v1, v2, v3, v4;
	glm::vec3 normal;
	float r, g, b;

	normal = glm::vec3(0, 0, 1);
	r = 1;
	g = 1;
	b = 1;
	v1 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 0, 0), normal, r, g, b);
	v2 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 0, 0), normal, r, g, b);
	v3 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 1, 0), normal, r, g, b);
	v4 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 1, 0), normal, r, g, b);
	renderer.addTriangleToMesh(playerModelID, v1, v2, v3);
	renderer.addTriangleToMesh(playerModelID, v1, v3, v4);

	normal = glm::vec3(-1, 0, 0);
	r = 0;
	g = 1;
	b = 0.5f;
	v1 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 0, -1), normal, r, g, b);
	v2 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 0, 0), normal, r, g, b);
	v3 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 1, 0), normal, r, g, b);
	v4 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 1, -1), normal, r, g, b);
	renderer.addTriangleToMesh(playerModelID, v1, v2, v3);
	renderer.addTriangleToMesh(playerModelID, v1, v3, v4);

	normal = glm::vec3(1, 0, 0);
	r = 1;
	g = 0;
	b = 0;
	v1 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 0, 0), normal, r, g, b);
	v2 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 0, -1), normal, r, g, b);
	v3 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 1, -1), normal, r, g, b);
	v4 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 1, 0), normal, r, g, b);
	renderer.addTriangleToMesh(playerModelID, v1, v2, v3);
	renderer.addTriangleToMesh(playerModelID, v1, v3, v4);

	normal = glm::vec3(0, 0, -1);
	r = 0;
	g = 1;
	b = 0;
	v1 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 0, -1), normal, r, g, b);
	v2 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 0, -1), normal, r, g, b);
	v3 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 1, -1), normal, r, g, b);
	v4 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 1, -1), normal, r, g, b);
	renderer.addTriangleToMesh(playerModelID, v1, v2, v3);
	renderer.addTriangleToMesh(playerModelID, v1, v3, v4);

	normal = glm::vec3(0, 1, 0);
	r = 1;
	g = 0.5f;
	b = 0;
	v1 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 1, 0), normal, r, g, b);
	v2 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 1, 0), normal, r, g, b);
	v3 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 1, -1), normal, r, g, b);
	v4 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 1, -1), normal, r, g, b);
	renderer.addTriangleToMesh(playerModelID, v1, v2, v3);
	renderer.addTriangleToMesh(playerModelID, v1, v3, v4);

	normal = glm::vec3(0, -1, 0);
	r = 0.5f;
	g = 0;
	b = 1;
	v1 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 0, -1), normal, r, g, b);
	v2 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 0, -1), normal, r, g, b);
	v3 = renderer.addVertexToMesh(playerModelID, glm::vec3(1, 0, 0), normal, r, g, b);
	v4 = renderer.addVertexToMesh(playerModelID, glm::vec3(0, 0, 0), normal, r, g, b);
	renderer.addTriangleToMesh(playerModelID, v1, v2, v3);
	renderer.addTriangleToMesh(playerModelID, v1, v3, v4);

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

	int mouseDX, mouseDY;
	mouseDX = ts::Mouse::getLastMove().x;
	mouseDY = ts::Mouse::getLastMove().y;
	camera.rotateWithMove(mouseDX, mouseDY);
}

void Player::update(time_t dt) {
	//TODO check collisions
	//TODO make world class

	move(moveVector);

	moveVector = glm::vec3();	//Reset move vector every frame;
}

void Player::draw(glm::mat4 * viewMat) {
	shaderProgram.useProgram();

	glm::mat4 modelMatrix = glm::translate(32.f, 30.f, 10.f) * glm::rotate(180.f, 0.f, 1.f, 0.f);

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
	position += moveVector;
	camera.move(moveVector);
}

glm::mat4 * Player::getCameraViewMatrix() {
	return camera.getViewMatrix();
}
