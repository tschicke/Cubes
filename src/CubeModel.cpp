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
#include <vector>

#include "MathHelper.h"

#include "Entity.h"

CubeModel::CubeModel() {
	fileName = NULL;
	parentEntity = NULL;
	modelLoaded = false;
	modelMatNeedsUpdate = false;
	needsIndexBufferUpdate = false;
	numVertices = 0;
	numVerticesToDraw = 0;
	blockArray = NULL;
	scale = 1;
	modelWidth = modelHeight = modelDepth = 0;
	yaw = pitch = 0;
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
	yaw = pitch = 0;

	if (fileName != NULL) {
		loadModel(fileName);
	}
}

void CubeModel::render() {
	if (modelLoaded && vertBuffLoaded && indexBuffLoaded) {
		if (modelMatNeedsUpdate) {
			modelMatrix = glm::translate(glm::vec3(parentEntity->position))
			* glm::rotate((float)parentEntity->yaw, 0.f, 1.f, 0.f) * glm::rotate((float)parentEntity->pitch, 0.f, 0.f, 1.f);//Temp
			//TODO make yaw and pitch in Entity not in CubeModel
			//TODO look into using quaternions for rotation
//			modelMatrix = glm::translate(parentEntity->position);
			modelMatNeedsUpdate = false;
		}

		shaderProgram.useProgram();

		shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
		shaderProgram.setUniform("viewMatrix", parentEntity->parentWorld->getMainPlayer()->getCameraViewMatrix(), 1);
		shaderProgram.setUniform("projectionMatrix", &projectionMatrix, 1);

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

void CubeModel::update() {
	if(needsIndexBufferUpdate){
		remakeIndexBuffer();
		needsIndexBufferUpdate = false;
	}
}

void CubeModel::loadModel(const char* fileName) {
	if (modelLoaded || fileName == NULL) {
		return;
	}

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

	modelWidth = *(int *) &header[2]; //FIXME fix the way these are changed to ints
	modelHeight = *(int *) &header[6];
	modelDepth = *(int *) &header[10];

	scale = 1/32.f;//TODO load this from file

	delete blockArray;
	blockArray = new ColorBlock[modelWidth * modelHeight * modelDepth];
	parentEntity->halfDimentions = glm::vec3(modelWidth / 2.f, modelHeight / 2.f, modelDepth / 2.f) * scale;//TODO make collision bounding box more accurate

	int numCubes = modelWidth * modelHeight * modelDepth;
	int bytesPerCube = 4; //1 byte for each color channel, 1 byte for drawn;
	int bufferSize = numCubes * bytesPerCube;
	char * buffer = new char[bufferSize];

	file.read(buffer, bufferSize);

	numVertices = numCubes * 24;
	int numVertices = numCubes * 24 * 3;//Numvertices * 3 floats per vertex
	int numColors = numCubes * 24 * 3;
	int numNormals = numCubes * 24 * 3;
	int numIndices = numCubes * 36;

	if(vertBuffLoaded || indexBuffLoaded){
		deleteBuffers();
	}

	initBuffersWithSize((numVertices + numColors + numNormals) * sizeof(float), numIndices * sizeof(unsigned int));

	for (int x = 0; x < modelWidth; ++x) {
		for (int y = 0; y < modelHeight; ++y) {
			for (int z = 0; z < modelDepth; ++z) {
				int blockIndex = x * modelHeight * modelDepth + y * modelDepth + z;
				ColorBlock currentBlock;

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

				blockArray[blockIndex] = currentBlock;

				updateBlockAtPosition(x, y, z);
			}
		}
	}

	remakeIndexBuffer();

	delete[] buffer;
	modelLoaded = true;
	modelMatNeedsUpdate = true;
}

void CubeModel::markNeedsMatrixUpdate() {
	modelMatNeedsUpdate = true;
}

void CubeModel::saveModel() {
	//TODO implement model saving
}

void CubeModel::remakeIndexBuffer() {
	std::vector<unsigned int> indices;

	unsigned int cubeIndexData[] = {
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

	for (int x = 0; x < modelWidth; ++x) {
		for (int y = 0; y < modelHeight; ++y) {
			for (int z = 0; z < modelDepth; ++z) {
				int blockIndex = x * modelHeight * modelDepth + y * modelDepth + z;
				int blockIndexXMinusOne = (x - 1) * modelHeight * modelDepth + y * modelDepth + z;
				int blockIndexXPlusOne = (x + 1) * modelHeight * modelDepth + y * modelDepth + z;
				int blockIndexYMinusOne = x * modelHeight * modelDepth + (y - 1) * modelDepth + z;
				int blockIndexYPlusOne = x * modelHeight * modelDepth + (y + 1) * modelDepth + z;
				int blockIndexZMinusOne = x * modelHeight * modelDepth + y * modelDepth + z - 1;
				int blockIndexZPlusOne = x * modelHeight * modelDepth + y * modelDepth + z + 1;

				int indexOffset = blockIndex * 24;

				ColorBlock block = blockArray[blockIndex];

				if (block.isDrawn()) {
					if (z != modelDepth - 1) {
						if (!blockArray[blockIndexZPlusOne].isDrawn()) { //Front
							for (int i = 0; i < 6; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 0; i < 6; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (z != 0) {
						if (!blockArray[blockIndexZMinusOne].isDrawn()) { //Back
							for (int i = 6; i < 12; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 6; i < 12; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (x != 0) {
						if (!blockArray[blockIndexXMinusOne].isDrawn()) { //Left
							for (int i = 12; i < 18; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 12; i < 18; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (x != modelWidth - 1) {
						if (!blockArray[blockIndexXPlusOne].isDrawn()) { //Right
							for (int i = 18; i < 24; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 18; i < 24; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (y != modelHeight - 1) {
						if (!blockArray[blockIndexYPlusOne].isDrawn()) { //Top
							for (int i = 24; i < 30; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 24; i < 30; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (y != 0) {
						if (!blockArray[blockIndexYMinusOne].isDrawn()) { //Bottom
							for (int i = 30; i < 36; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 30; i < 36; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}
				}
			}
		}
	}

	numVerticesToDraw = indices.size();
	needsIndexBufferUpdate = false;

	substituteDataToIndexBuffer(numVerticesToDraw * sizeof(unsigned int), 0, &indices[0]);
}

void CubeModel::updateBlockAtPosition(int x, int y, int z) {
	float cubeSize = scale;
	int blockIndex = x * modelHeight * modelDepth + y * modelDepth + z;
	int modelSize = modelWidth * modelHeight * modelDepth;

	int numVerticesPerCube = 24;
	int numVerticesPerModel = numVerticesPerCube * modelSize * 3; //num floats in vertex portion of data
	int numColorsPerModel = numVerticesPerCube * modelSize * 3; //num floats in texture portion of data

	int vertexIndex = blockIndex * numVerticesPerCube * 3;
	int colorIndex = blockIndex * numVerticesPerCube * 3;
	int normalIndex = blockIndex * numVerticesPerCube * 3;

	float cubeVertexData[] = {
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

	float cubeColorData[24 * 3];

	float cubeNormalData[] = {
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

	for (int i = 0; i < 24; ++i) {
		cubeVertexData[(i * 3)] += (x - (modelWidth / 2.f)) * scale;//TODO should this be done like this?
		cubeVertexData[(i * 3) + 1] += y * scale;
		cubeVertexData[(i * 3) + 2] += (z - (modelDepth / 2.f)) * scale;

		cubeColorData[(i * 3)] = blockArray[blockIndex].getColor().r;
		cubeColorData[(i * 3) + 1] = blockArray[blockIndex].getColor().g;
		cubeColorData[(i * 3) + 2] = blockArray[blockIndex].getColor().b;
	}

	substituteDataToVertexBuffer(sizeof(cubeVertexData), vertexIndex * sizeof(float), cubeVertexData);
	substituteDataToVertexBuffer(sizeof(cubeColorData), (numVerticesPerModel + colorIndex) * sizeof(float), (float *)cubeColorData);
	substituteDataToVertexBuffer(sizeof(cubeNormalData), (numVerticesPerModel + numColorsPerModel + normalIndex) * sizeof(float), cubeNormalData);
	markDirty();
}

void CubeModel::markDirty() {
	needsIndexBufferUpdate = true;
}

