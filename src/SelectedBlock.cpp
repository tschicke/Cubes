/*
 * SelectedBlock.cpp
 *
 *  Created on: Jun 17, 2013
 *      Author: Tyler
 */

#include "SelectedBlock.h"

#include "Blocks/Block.h"

#include "Player.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>

SelectedBlock::SelectedBlock() {
	block = NULL;
	x = y = z = 0;
	face = 0;
	drawable = false;
	parentPlayer = NULL;
	modelMatNeedsUpdate = false;
	numVertices = 0;
	numVerticesToDraw = 0;
}

SelectedBlock::SelectedBlock(int x, int y, int z, Block* block, Face face, bool drawable, Player * parentPlayer) {
	this->block = block;
	this->x = x;
	this->y = y;
	this->z = z;
	this->face = face;
	this->drawable = drawable;
	this->parentPlayer = parentPlayer;
	modelMatNeedsUpdate = false;
	numVertices = 0;
	numVerticesToDraw = 0;

	if(drawable){
		loadModel();
	}
}

SelectedBlock::~SelectedBlock() {
}

void SelectedBlock::setDrawable(bool drawable) {
	if(this->drawable == false && drawable == true){
		loadModel();
	}
	this->drawable = drawable;
}

glm::vec3 SelectedBlock::getAddBlockPosition() {
	glm::vec3 addBlockPosition = glm::vec3(x, y, z);
	if(face == face_back){
		addBlockPosition.z -= 1;
	} else if(face == face_front){
		addBlockPosition.z += 1;
	} else if(face == face_left){
		addBlockPosition.x -= 1;
	} else if(face == face_right){
		addBlockPosition.x += 1;
	} else if(face == face_bottom){
		addBlockPosition.y -= 1;
	} else if(face == face_top){
		addBlockPosition.y += 1;
	}

	return addBlockPosition;
}

void SelectedBlock::copy(const SelectedBlock& copy) {
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
	this->block = copy.block;
	this->face = copy.face;

	modelMatNeedsUpdate = true;
}

void SelectedBlock::loadModel() {
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

	int vertexBufferSize = 8 * 3;
	int indexBufferSize = 12 * 2;
	initBuffersWithSize(vertexBufferSize * sizeof(float), indexBufferSize * sizeof(unsigned int));

	float vertexData[] = {//TODO change extra amount on block
			-0.005f, -0.005f, -0.005f,
			1.005f, -0.005f, -0.005f,
			1.005f, 1.005f, -0.005f,
			-0.005f, 1.005f, -0.005f,
			-0.005f, -0.005f, 1.005f,
			1.005f, -0.005f, 1.005f,
			1.005f, 1.005f, 1.005f,
			-0.005f, 1.005f, 1.005f,
	};

	unsigned int indexData[] = {
			0, 1,
			1, 2,
			2, 3,
			3, 0,

			4, 5,
			5, 6,
			6, 7,
			7, 4,

			0, 4,
			1, 5,
			2, 6,
			3, 7,
	};

	substituteDataToVertexBuffer(vertexBufferSize * sizeof(float), 0, vertexData);
	substituteDataToIndexBuffer(indexBufferSize * sizeof(unsigned int), 0, indexData);

	numVertices = 8;
	numVerticesToDraw = 24;
	modelMatNeedsUpdate = true;
}

void SelectedBlock::render() {
	if(drawable && (block != NULL)){
		if (modelMatNeedsUpdate) {
			modelMatrix = glm::translate(x, y, z);
			modelMatNeedsUpdate = false;
		}

		shaderProgram.useProgram();

		shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
		shaderProgram.setUniform("viewMatrix", parentPlayer->getCameraViewMatrix(), 1);
		shaderProgram.setUniform("projectionMatrix", &projectionMatrix, 1);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); //Vertices

		glDrawElements(GL_LINES, numVerticesToDraw, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glUseProgram(0);
	}
}
