/*
 * ChunkRenderer.cpp
 *
 *  Created on: May 19, 2013
 *      Author: Tyler
 */

#include <iostream>
#include <fstream>

#include "ChunkRenderer.h"

#include "Chunk.h"
#include "Player.h"

#include "SpriteSheet.h"

#include <glm/gtx/transform.hpp>

#include <vector>

ChunkRenderer::ChunkRenderer() {
	modelMatNeedsUpdate = false;
	parentChunk = NULL;
	numVerticesToDraw = 0;
	needsIndexBufferRemake = false;
	blockNeedsUpdate = NULL;
}

ChunkRenderer::ChunkRenderer(int x, int y, int z, Chunk * parentChunk) {
	init(x, y, z, parentChunk);
}

void ChunkRenderer::init(int x, int y, int z, Chunk * parentChunk) {
	this->parentChunk = parentChunk;

	Shader vertexShader;
	vertexShader.loadShader("shaders/textureShader.vert", GL_VERTEX_SHADER);

	Shader fragmentShader;
	fragmentShader.loadShader("shaders/textureShader.frag", GL_FRAGMENT_SHADER);

	shaderProgram.createProgram();
	shaderProgram.addShader(&vertexShader);
	shaderProgram.addShader(&fragmentShader);
	shaderProgram.linkProgram();

	vertexShader.deleteShader();
	fragmentShader.deleteShader();

	chunkPosition = glm::vec3(x, y, z);
	modelMatNeedsUpdate = true;

	blockNeedsUpdate = new bool[Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE];
	for(int i = 0; i < Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE; ++i){
		blockNeedsUpdate[i] = false;
	}

	int numVerticesPerChunk = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * 24 * 3;
	int numTexCoordsPerChunk = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * 24 * 2;
	int numNormalsPerChunk = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * 24 * 3;
	int numIndicesPerChunk = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * 36;

	initBuffersWithSize((numVerticesPerChunk + numTexCoordsPerChunk + numNormalsPerChunk) * sizeof(float), numIndicesPerChunk * sizeof(unsigned int));

//	float * vertexArray = new float[numVerticesPerChunk + numTexCoordsPerChunk + numNormalsPerChunk];
//
//	/*   Cube Diagram
//	 *
//	 * 		  p7__________p6
//	 * 		   /|		 /|
//	 * 		p3/_|_____p2/ |
//	 * 		 |  |	   |  |
//	 * 		 |	|p4____|__|p5
//	 * 		 | /	   | /
//	 * 	   p0|/________|/p1
//	 */
//
//	float cubeSize = Block::cubeSize;
//
//	float cubeVertexData[] = {
//			//Front
//			0, 0, cubeSize,
//			cubeSize, 0, cubeSize,
//			cubeSize, cubeSize, cubeSize,
//			0, cubeSize, cubeSize,
//
//			//Back
//			cubeSize, 0, 0,
//			0, 0, 0,
//			0, cubeSize, 0,
//			cubeSize, cubeSize, 0,
//
//			//Left
//			0, 0, 0,
//			0, 0, cubeSize,
//			0, cubeSize, cubeSize,
//			0, cubeSize, 0,
//
//			//Right
//			cubeSize, 0, cubeSize,
//			cubeSize, 0, 0,
//			cubeSize, cubeSize, 0,
//			cubeSize, cubeSize, cubeSize,
//
//			//Top
//			0, cubeSize, cubeSize,
//			cubeSize, cubeSize, cubeSize,
//			cubeSize, cubeSize, 0,
//			0, cubeSize, 0,
//
//			//Bottom
//			0, 0, 0,
//			cubeSize, 0, 0,
//			cubeSize, 0, cubeSize,
//			0, 0, cubeSize
//	};
//
//	float texElementSize = ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getWidth();
//
//	float cubeTexData[] = {
//			//Front
//			0, 2 * texElementSize,
//			texElementSize, 2 * texElementSize,
//			texElementSize, texElementSize,
//			0, texElementSize,
//
//			//Back
//			0, 2 * texElementSize,
//			texElementSize, 2 * texElementSize,
//			texElementSize, texElementSize,
//			0, texElementSize,
//
//			//Left
//			0, 2 * texElementSize,
//			texElementSize, 2 * texElementSize,
//			texElementSize, texElementSize,
//			0, texElementSize,
//
//			//Right
//			0, 2 * texElementSize,
//			texElementSize, 2 * texElementSize,
//			texElementSize, texElementSize,
//			0, texElementSize,
//
//			//Top
//			0, texElementSize,
//			texElementSize, texElementSize,
//			texElementSize, 0,
//			0, 0,
//
//			//Bottom
//			texElementSize, texElementSize,
//			2 * texElementSize,
//			texElementSize, 2 * texElementSize,
//			0, texElementSize, 0
//	};
//
//	float cubeNormalData[] = {
//			0, 0, 1,
//			0, 0, 1,
//			0, 0, 1,
//			0, 0, 1,
//
//			0, 0, -1,
//			0, 0, -1,
//			0, 0, -1,
//			0, 0, -1,
//
//			-1, 0, 0,
//			-1, 0, 0,
//			-1, 0, 0,
//			-1, 0, 0,
//
//			1, 0, 0,
//			1, 0, 0,
//			1, 0, 0,
//			1, 0, 0,
//
//			0, 1, 0,
//			0, 1, 0,
//			0, 1, 0,
//			0, 1, 0,
//
//			0, -1, 0,
//			0, -1, 0,
//			0, -1, 0,
//			0, -1, 0
//	};
//
//	Block ** blockArray = parentChunk->blockStorage->getBlockArray();
//
//	for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
//		for (int y = 0; y < Chunk::CHUNK_SIZE; ++y) {
//			for (int z = 0; z < Chunk::CHUNK_SIZE; ++z) {
//				int blockIndex = x * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE + y * Chunk::CHUNK_SIZE + z;
//
//				int numVerticesPerCube = 24;
//
//				int vertexIndex = blockIndex * numVerticesPerCube * 3;
//				int texIndex = blockIndex * numVerticesPerCube * 2;
//				int normalIndex = blockIndex * numVerticesPerCube * 3;
//
//				Block * block = blockArray[blockIndex];
//
//				if (block != NULL && block->isDrawn()) {
//					for (int i = 0; i < numVerticesPerCube; ++i) {
//						vertexArray[vertexIndex + (i * 3)] = cubeVertexData[(i * 3)] + x;
//						vertexArray[vertexIndex + (i * 3) + 1] = cubeVertexData[(i * 3) + 1] + y;
//						vertexArray[vertexIndex + (i * 3) + 2] = cubeVertexData[(i * 3) + 2] + z;
//
//						vertexArray[numVerticesPerChunk + texIndex + (i * 2)] = cubeTexData[(i * 2)] + block->getBaseTextureX();
//						vertexArray[numVerticesPerChunk + texIndex + (i * 2) + 1] = cubeTexData[(i * 2) + 1] + block->getBaseTextureY();
//
//						vertexArray[numVerticesPerChunk + numTexCoordsPerChunk + normalIndex + (i * 3)] = cubeNormalData[(i * 3)];
//						vertexArray[numVerticesPerChunk + numTexCoordsPerChunk + normalIndex + (i * 3) + 1] = cubeNormalData[(i * 3) + 1];
//						vertexArray[numVerticesPerChunk + numTexCoordsPerChunk + normalIndex + (i * 3) + 2] = cubeNormalData[(i * 3) + 2];
//					}
//				}
//
//				blockNeedsUpdate[blockIndex] = false;
//			}
//		}
//	}
//
//	substituteDataToVertexBuffer((numVerticesPerChunk + numTexCoordsPerChunk + numNormalsPerChunk) * sizeof(float), 0, vertexArray);
//
//	remakeIndexBuffer();
//
//	delete[] vertexArray;
}

ChunkRenderer::~ChunkRenderer() {
//	deleteBuffers();
}

void ChunkRenderer::setChunkPosition(int x, int y, int z) {
	chunkPosition = glm::vec3(x, y, z);
	modelMatNeedsUpdate = true;
}

void ChunkRenderer::remakeIndexBuffer() {
	std::vector<unsigned int> indices;

	Block ** blockArray = parentChunk->blockStorage->getBlockArray();

	int chunkSize = Chunk::CHUNK_SIZE;

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

	for(int x = 0; x < chunkSize; ++x){
		for(int y = 0; y < chunkSize; ++y){
			for(int z = 0; z < chunkSize; ++z){
				int blockIndex = x * chunkSize * chunkSize + y * chunkSize + z;
				int blockIndexXMinusOne = (x - 1) * chunkSize * chunkSize + y * chunkSize + z;
				int blockIndexXPlusOne = (x + 1) * chunkSize * chunkSize + y * chunkSize + z;
				int blockIndexYMinusOne = x * chunkSize * chunkSize + (y - 1) * chunkSize + z;
				int blockIndexYPlusOne = x * chunkSize * chunkSize + (y + 1) * chunkSize + z;
				int blockIndexZMinusOne = x * chunkSize * chunkSize + y * chunkSize + z - 1;
				int blockIndexZPlusOne = x * chunkSize * chunkSize + y * chunkSize + z + 1;

				int indexOffset = blockIndex * 24;

				Block * block = blockArray[blockIndex];

				if (block != NULL && block->isDrawn()) {
					if (z != chunkSize - 1) {
						if (blockArray[blockIndexZPlusOne] != NULL && !blockArray[blockIndexZPlusOne]->isDrawn()) { //Front
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
						if (blockArray[blockIndexZMinusOne] != NULL && !blockArray[blockIndexZMinusOne]->isDrawn()) { //Back
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
						if (blockArray[blockIndexXMinusOne] != NULL && !blockArray[blockIndexXMinusOne]->isDrawn()) { //Left
							for (int i = 12; i < 18; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 12; i < 18; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (x != chunkSize - 1) {
						if (blockArray[blockIndexXPlusOne] != NULL && !blockArray[blockIndexXPlusOne]->isDrawn()) { //Right
							for (int i = 18; i < 24; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 18; i < 24; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (y != chunkSize - 1) {
						if (blockArray[blockIndexYPlusOne] != NULL && !blockArray[blockIndexYPlusOne]->isDrawn()) { //Top
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
						if (blockArray[blockIndexYMinusOne] != NULL && !blockArray[blockIndexYMinusOne]->isDrawn()) { //Bottom
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

	substituteDataToIndexBuffer(numVerticesToDraw * sizeof(unsigned int), 0, &indices[0]);
}

void ChunkRenderer::update(time_t dt) {
	if (parentChunk == NULL)
		return;

	for(int x = 0; x < Chunk::CHUNK_SIZE; ++x){
		for(int y = 0; y < Chunk::CHUNK_SIZE; ++y){
			for(int z = 0; z < Chunk::CHUNK_SIZE; ++z){
				int blockIndex = x * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE + y * Chunk::CHUNK_SIZE + z;
				if(blockNeedsUpdate[blockIndex] == true){
					updateBlockAtPosition(x, y, z);
				}
				blockNeedsUpdate[blockIndex] = false;
			}
		}
	}

	if(needsIndexBufferRemake){
		remakeIndexBuffer();
		needsIndexBufferRemake = false;
	}

	std::cout << "chunk renderer update\n";
}

void ChunkRenderer::render(Player * player) {
	if (modelMatNeedsUpdate) {
		modelMatrix = glm::translate(chunkPosition);
		modelMatNeedsUpdate = false;
	}

	shaderProgram.useProgram();

	ts::SpriteSheet::defaultSpriteSheet->useTexture();

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

	int numCubes = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE;
	int numVertices = numCubes * 24;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); //Vertices
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) (numVertices * 3 * sizeof(float))); //Texture Coordinates
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) (numVertices * 5 * sizeof(float))); //Normals

	glDrawElements(GL_TRIANGLES, numVerticesToDraw, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(0);

	ts::SpriteSheet::unbindTextures();
}

void ChunkRenderer::updateBlockAtPosition(int x, int y, int z) {
	float cubeSize = Block::cubeSize;
	BlockStorage * blockStorage = parentChunk->blockStorage;
	int blockIndex = x * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE + y * Chunk::CHUNK_SIZE + z;
	int chunkSize = Chunk::CHUNK_SIZE;

	int numVerticesPerCube = 24;
	int numVerticesPerChunk = numVerticesPerCube * chunkSize * chunkSize * chunkSize * 3;//num floats in vertex portion of data
	int numTexCoordsPerChunk = numVerticesPerCube * chunkSize * chunkSize * chunkSize * 2;//num floats in texture portion of data

	int vertexIndex = blockIndex * numVerticesPerCube * 3;
	int texIndex = blockIndex * numVerticesPerCube * 2;
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

	float texElementSize = ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getWidth();

	float cubeTexData[] = {
			//Front
			0, 2 * texElementSize,
			texElementSize, 2 * texElementSize,
			texElementSize, texElementSize,
			0, texElementSize,

			//Back
			0, 2 * texElementSize,
			texElementSize, 2 * texElementSize,
			texElementSize, texElementSize,
			0, texElementSize,

			//Left
			0, 2 * texElementSize,
			texElementSize, 2 * texElementSize,
			texElementSize, texElementSize,
			0, texElementSize,

			//Right
			0, 2 * texElementSize,
			texElementSize, 2 * texElementSize,
			texElementSize, texElementSize,
			0, texElementSize,

			//Top
			0, texElementSize,
			texElementSize, texElementSize,
			texElementSize, 0,
			0, 0,

			//Bottom
			texElementSize, texElementSize,
			2 * texElementSize,
			texElementSize, 2 * texElementSize,
			0, texElementSize, 0
	};

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

	for (int i = 0; i < 24; ++i){
		cubeVertexData[(i * 3)] += x;
		cubeVertexData[(i * 3) + 1] += y;
		cubeVertexData[(i * 3) + 2] += z;

		cubeTexData[(i * 2)] += blockStorage->getBlockArray()[blockIndex]->getBaseTextureX();
		cubeTexData[(i * 2) + 1] += blockStorage->getBlockArray()[blockIndex]->getBaseTextureY();
	}

	substituteDataToVertexBuffer(sizeof(cubeVertexData), vertexIndex * sizeof(float), cubeVertexData);
	substituteDataToVertexBuffer(sizeof(cubeTexData), (numVerticesPerChunk + texIndex) * sizeof(float), cubeTexData);
	substituteDataToVertexBuffer(sizeof(cubeNormalData), (numVerticesPerChunk + numTexCoordsPerChunk + normalIndex) * sizeof(float), cubeNormalData);
}

void ChunkRenderer::markBlockAtPositionDirty(int x, int y, int z) {
	x %= Chunk::CHUNK_SIZE;
	x = (x < 0 ? x + Chunk::CHUNK_SIZE : x);
	y %= Chunk::CHUNK_SIZE;
	y = (y < 0 ? y + Chunk::CHUNK_SIZE : y);
	z %= Chunk::CHUNK_SIZE;
	z = (z < 0 ? z + Chunk::CHUNK_SIZE : z);
	blockNeedsUpdate[x * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE + y * Chunk::CHUNK_SIZE + z] = true;
}

void ChunkRenderer::markIndicesDirty() {
	needsIndexBufferRemake = true;
}
