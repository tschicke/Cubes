/*
 * EntityRenderer.cpp
 *
 *  Created on: Jun 29, 2013
 *      Author: Tyler
 */

#include "EntityRenderer.h"

#include "Player.h"

#include <glm/gtx/transform.hpp>

#include <iostream>

EntityRenderer::EntityRenderer() {
	modelMatNeedsUpdate = false;
	numVerticesToDraw = 0;
	numVertices = 0;
	parentEntity = NULL;
}

EntityRenderer::EntityRenderer(Entity * parent, const char * modelFile) {
	init(parent, modelFile);
}

EntityRenderer::~EntityRenderer() {
}

void EntityRenderer::init(Entity * parent, const char * modelFile) {
	modelMatNeedsUpdate = true;

	parentEntity = parent;

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

	loadModel(modelFile);
}

void EntityRenderer::markNeedsMatrixUpdate() {
	modelMatNeedsUpdate = true;
}

void EntityRenderer::loadModel(const char * modelFile) {
	float cubeSize = 0.4f;

	float vertexData[] = {
			//Front
			0, 0, cubeSize,
			cubeSize, 0, cubeSize,
			cubeSize, cubeSize, cubeSize,
			0, cubeSize, cubeSize,

			//Back
			cubeSize, 0, 0,
			0, 0, 0,
			0, cubeSize, 0,
			cubeSize, cubeSize, 0,

			//Left
			0, 0, 0,
			0, 0, cubeSize,
			0, cubeSize, cubeSize,
			0, cubeSize, 0,

			//Right
			cubeSize, 0, cubeSize,
			cubeSize, 0, 0,
			cubeSize, cubeSize, 0,
			cubeSize, cubeSize, cubeSize,

			//Top
			0, cubeSize, cubeSize,
			cubeSize, cubeSize, cubeSize,
			cubeSize, cubeSize, 0,
			0, cubeSize, 0,

			//Bottom
			0, 0, 0,
			cubeSize, 0, 0,
			cubeSize, 0, cubeSize,
			0, 0, cubeSize
	};

	float colorData[] = {
			//Front
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
	};

	float normalData[] = {
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,

			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,

			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,

			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,

			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0
	};

	unsigned int indices[] = {
			//Front
			0, 1, 2,
			0, 2, 3,

			//Back
			4, 5, 6,
			4, 6, 7,

			//Left
			8, 9, 10,
			8, 10, 11,

			//Right
			12, 13, 14,
			12, 14, 15,

			//Top
			16, 17, 18,
			16, 18, 19,

			//Bottom
			20, 21, 22,
			20, 22, 23
	};

	initBuffersWithSize(sizeof(vertexData) + sizeof(colorData) + sizeof(normalData), sizeof(indices));
	substituteDataToVertexBuffer(sizeof(vertexData), 0, vertexData);
	substituteDataToVertexBuffer(sizeof(colorData), sizeof(vertexData), colorData);
	substituteDataToVertexBuffer(sizeof(normalData), sizeof(vertexData) + sizeof(colorData), normalData);
	substituteDataToIndexBuffer(sizeof(indices) , 0, indices);

	numVerticesToDraw = 36;
	numVertices = 24;
}

void EntityRenderer::render(Player* player) {
	if (modelMatNeedsUpdate) {
		modelMatrix = glm::translate(parentEntity->position);
		std::cout << parentEntity->position.x << '\n';
		modelMatNeedsUpdate = false;
	}

	shaderProgram.useProgram();

	shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
	shaderProgram.setUniform("viewMatrix", player->getCameraViewMatrix(), 1);
	shaderProgram.setUniform("projectionMatrix", &projectionMatrix, 1);

	glm::vec3 testColor(1.f, 1.f, 1.f);
	shaderProgram.setUniform("testColor", &testColor, 1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); //Vertices
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) (sizeof(float) * numVertices * 3)); //Colors
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) (sizeof(float) * numVertices * 3 * 2)); //Normals

	glDrawElements(GL_TRIANGLES, numVerticesToDraw, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(0);
}
