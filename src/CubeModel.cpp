/*
 * CubeModel.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: Tyler
 */

#include "CubeModel.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "World.h"

#include <iostream>
#include <fstream>

#include "Entity.h"

CubeModel::CubeModel() {
	fileName = NULL;
	parentEntity = NULL;
	modelLoaded = false;
	modelMatNeedsUpdate = false;
	numVertices = 0;
	numVerticesToDraw = 0;
	blockArray = NULL;
}

CubeModel::CubeModel(const char* fileName, Entity * parentEnity) {
	init(fileName, parentEnity);
}

CubeModel::~CubeModel() {
//	saveModel();
}

void CubeModel::init(const char* fileName, Entity* parentEnity) {
	this->fileName = fileName;
	this->parentEntity = parentEnity;
	modelLoaded = false;
	modelMatNeedsUpdate = false;
	numVertices = 0;
	numVerticesToDraw = 0;
	blockArray = NULL;

	loadModel(fileName);
}

void CubeModel::render() {
	if (modelLoaded && vertBuffLoaded && indexBuffLoaded) {
		if (modelMatNeedsUpdate) {
			modelMatrix = glm::translate(parentEntity->position);
			modelMatNeedsUpdate = false;
		}

		shaderProgram.useProgram();

		shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
		shaderProgram.setUniform("viewMatrix", parentEntity->parentWorld->getMainPlayer()->getCameraViewMatrix(), 1);
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
}

void CubeModel::loadModel(const char* fileName) {
	if (modelLoaded || fileName == NULL) {
		return;
	}

	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "file could not be opened\n";
		return;
	}

	char header[14];
	file.read(header, 14);

	if (header[0] != 'c' || header[1] != 'm') {
		std::cout << "wrong file format\n";
		return;
	}

	int width = *(int *) &header[2]; //FIXME fix the way these are changed to ints
	int height = *(int *) &header[6];
	int depth = *(int *) &header[10];

	delete blockArray;
	blockArray = new ColorBlock[width * height * depth];
	parentEntity->halfDimentions = glm::vec3(width / 2, height / 2, depth / 2);

	int numCubes = width * height * depth;
	int bytesPerCube = 4; //1 byte for each color channel, 1 byte for drawn;
	int bufferSize = numCubes * bytesPerCube;
	char * buffer = new char[bufferSize];

	file.read(buffer, bufferSize);

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			for (int z = 0; z < depth; ++z) {
				int blockIndex = x * height * depth + y * depth + z;
				ColorBlock currentBlock = blockArray[blockIndex];

				bool drawn = *(bool *) &buffer[blockIndex * bytesPerCube];
				glm::vec3 blockColor;

				unsigned char r = buffer[blockIndex * bytesPerCube + 1];
				unsigned char g = buffer[blockIndex * bytesPerCube + 2];
				unsigned char b = buffer[blockIndex * bytesPerCube + 3];

				blockColor.r = r / 255.f;
				blockColor.g = g / 255.f;
				blockColor.b = b / 255.f;

				currentBlock.setDrawn(drawn);
				currentBlock.setColor(blockColor);

//				updateBlockAtPosition(x, y, z);//TODO implement this function and finish the rendering part of this class
			}
		}
	}

	delete[] buffer;
	modelLoaded = true;
	modelMatNeedsUpdate = true;
}

void CubeModel::markNeedsMatrixUpdate() {
	modelMatNeedsUpdate = true;
}

void CubeModel::saveModel() {
}
