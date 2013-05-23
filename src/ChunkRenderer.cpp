/*
 * ChunkRenderer.cpp
 *
 *  Created on: May 19, 2013
 *      Author: Tyler
 */

#include "ChunkRenderer.h"

#include "Chunk.h"
#include "Player.h"

#include "SpriteSheet.h"

#include <gl/glew.h>

ChunkRenderer::ChunkRenderer() {
	modelMatNeedsUpdate = false;
}

ChunkRenderer::ChunkRenderer(int x, int y, int z, Block ** blockArray) {
	init(x, y, z, blockArray);
}

void ChunkRenderer::init(int x, int y, int z, Block ** blockArray) {
	Shader vertexShader;
	vertexShader.loadShader("shaders/textureShader.vert", GL_VERTEX_SHADER);

	Shader fragmentShader;
	fragmentShader.loadShader("shaders/textureShader.frag", GL_FRAGMENT_SHADER);

	ShaderProgram shaderProgram;
	shaderProgram.createProgram();
	shaderProgram.addShader(&vertexShader);
	shaderProgram.addShader(&fragmentShader);
	shaderProgram.linkProgram();

	vertexShader.deleteShader();
	fragmentShader.deleteShader();

	chunkPosition = glm::vec3(x, y, z);
	modelMatNeedsUpdate = true;

	int numVerticesPerChunk = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * 24 * 3;
	int numTexCoordsPerChunk = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * 24 * 2;
	int numIndicesPerChunk = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * 36;
	initBuffersWithSize((numVerticesPerChunk + numTexCoordsPerChunk) * sizeof(float), numIndicesPerChunk * sizeof(unsigned int));

	float * vertexArray = new float[numVerticesPerChunk + numTexCoordsPerChunk];
	unsigned int * indexArray = new unsigned int[numIndicesPerChunk];


	/*
	 *
	 * 		  p7__________p6
	 * 		   /|		 /|
	 * 		p3/_|_____p2/ |
	 * 		 |  |	   |  |
	 * 		 |	|p4____|__|p5
	 * 		 | /	   | /
	 * 	   p0|/________|/p1
	 */

	float cubeSize = Block::cubeSize;

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
		0, 2 * texElementSize,
		texElementSize, 2 * texElementSize,
		texElementSize, texElementSize,
		0, texElementSize,

		0, 2 * texElementSize,
		texElementSize, 2 * texElementSize,
		texElementSize, texElementSize,
		0, texElementSize,

		0, 2 * texElementSize,
		texElementSize, 2 * texElementSize,
		texElementSize, texElementSize,
		0, texElementSize,

		0, 2 * texElementSize,
		texElementSize, 2 * texElementSize,
		texElementSize, texElementSize,
		0, texElementSize,

		0, texElementSize,
		texElementSize, texElementSize,
		texElementSize, 0,
		0, 0,

		texElementSize, texElementSize,
		2 * texElementSize, texElementSize,
		2 * texElementSize, 0,
		texElementSize, 0
	};

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

	for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
		for (int y = 0; y < Chunk::CHUNK_SIZE; ++y) {
			for(int z = 0; z < Chunk::CHUNK_SIZE; ++z){
				int blockIndex = x * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE + y * Chunk::CHUNK_SIZE + z;

				int vertexIndex = blockIndex * 24 * 3;
				int texIndex = blockIndex * 24 * 2;
				int indexIndex = blockIndex * 36;

				Block * block = blockArray[blockIndex];


				//TODO complete this

			}
		}
	}
}

ChunkRenderer::~ChunkRenderer() {
	deleteBuffers();
}

void ChunkRenderer::setChunkPosition(int x, int y, int z) {
	chunkPosition = glm::vec3(x, y, z);
	modelMatNeedsUpdate = true;
}

void ChunkRenderer::render(Player * player) {
	if (modelMatNeedsUpdate) {
		modelMatrix = glm::translate(chunkPosition);
	}

	shaderProgram.useProgram();

	ts::SpriteSheet::defaultSpriteSheet->useTexture();

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	shaderProgram.setUniform("modelMatrix", &modelMatrix);
	shaderProgram.setUniform("viewMatrix", player->getCameraViewMatrix());
	shaderProgram.setUniform("projectionMatrix", &projectionMatrix);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	int numCubes = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * 36;
	int numVertices = numCubes * 24;
	int numIndices = numCubes * 36;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); //Vertices
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) (numVertices * 3)); //Texture Coordinates
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) (numVertices * 5)); //Normals

	glDrawElements(GL_TRIANGLES, numIndices, GL_FLOAT, (void *) 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	ts::SpriteSheet::unbindTextures();
}

void ChunkRenderer::addBlockAtPosition(int x, int y, int z) {
}
