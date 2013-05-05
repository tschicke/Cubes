/*
 * Chunk.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */
#include <iostream>

#include "Chunk.h"
#include "Shader.h"
#include "Texture.h"

#include <GL/glew.h>

#include <glm/glm.hpp>//Temp??
#include <glm/gtx/transform.hpp>//Temp??
#include <glm/gtc/noise.hpp>
#include "GameWindow.h"//Temp
#include "Noise.h"
#include <stdlib.h>
using namespace glm;
//Temp??

Chunk::Chunk() {
	blocks = NULL;
	loaded = false;
}

void Chunk::init(int startX, int startY, int startZ) {
	chunkPosition = glm::vec3(startX, startY, startZ);
	meshID.setColorType(ColorType_Texture);

	Renderer::getMainRenderer().createMesh(&meshID);

	blocks = new Block*[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

	Noise noise;

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				int height = (noise.smoothNoise2D(((x + startX) / 32.f), ((z + startZ) / 32.f)) + 1) * CHUNK_SIZE / 2;

				if (y + startY <= height) {
					blocks[indexOfBlockAt(x, y, z)] = new BlockDirt;
				} else {
					blocks[indexOfBlockAt(x, y, z)] = new BlockAir;
				}

//				float density = noise.smoothNoise3D(((x + startX) / 32.f), ((y + startY) / 32.f), ((z + startZ) / 32.f)) - (float)(y + startY) / (CHUNK_SIZE * 1);

//				if (density >= 0) {
//					blocks[indexOfBlockAt(x, y, z)] = new BlockDirt;
//				} else {
//					blocks[indexOfBlockAt(x, y, z)] = new BlockAir;
//				}
			}
		}
	}

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				Block * block = blocks[indexOfBlockAt(x, y, z)];
				if (block->isDrawn()) {
					createCube((x * Block::cubeSize), (y * Block::cubeSize), (z * Block::cubeSize)); //FIXME fix occlusion culling between chunks, and organize it better
				} else {
//					Renderer::getMainRenderer().addNullCube(meshID);
				}
			}
		}
	}

	Renderer::getMainRenderer().endMesh(&meshID);

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

	loaded = true;
}

Chunk::~Chunk() {
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				delete blocks[indexOfBlockAt(x, y, z)];
			}
		}
	}
	delete[] blocks;
}

glm::vec3 Chunk::getChunkPos() {
	return chunkPosition;
}

Block * Chunk::getBlockAtCoordinate(int x, int y, int z) {
	x %= CHUNK_SIZE;
	x = (x < 0 ? x + CHUNK_SIZE : x);
	y %= CHUNK_SIZE;
	y = (y < 0 ? y + CHUNK_SIZE : y);
	z %= CHUNK_SIZE;
	z = (z < 0 ? z + CHUNK_SIZE : z);
	return blocks[indexOfBlockAt(x, y, z)];
}

void Chunk::update(time_t dt) {
}

void Chunk::createCube(int x, int y, int z) {
	vec3 p1(x + 0, y + 0, z + Block::cubeSize);
	vec3 p2(x + Block::cubeSize, y + 0, z + Block::cubeSize);
	vec3 p3(x + Block::cubeSize, y + Block::cubeSize, z + Block::cubeSize);
	vec3 p4(x + 0, y + Block::cubeSize, z + Block::cubeSize);
	vec3 p5(x + 0, y + 0, z + 0);
	vec3 p6(x + Block::cubeSize, y + 0, z + 0);
	vec3 p7(x + Block::cubeSize, y + Block::cubeSize, z + 0);
	vec3 p8(x + 0, y + Block::cubeSize, z + 0);

	/*
	 *
	 * 		  p8__________p7
	 * 		   /|		 /|
	 * 		p4/_|_____p3/ |
	 * 		 |  |	   |  |
	 * 		 |	|p5____|__|p6
	 * 		 | /	   | /
	 * 	   p1|/________|/p2
	 */

	vec3 normal;

//	float r = ((float) (rand() % 10)) / 10;//For colored cubes
//	float g = ((float) (rand() % 10)) / 10;//For colored cubes
//	float b = ((float) (rand() % 10)) / 10;//For colored cubes

	int v1, v2, v3, v4, v5, v6, v7, v8;

	//Front
	if ((z != CHUNK_SIZE - 1 && !(blocks[indexOfBlockAt(x, y, z + 1)]->isDrawn())) || z == CHUNK_SIZE - 1) {
		normal = vec3(0, 0, 1);

		v1 = Renderer::getMainRenderer().addVertexToMesh(meshID, p1, normal, 0.0f, 0.0f);
		v2 = Renderer::getMainRenderer().addVertexToMesh(meshID, p2, normal, 0.5f, 0.0f);
		v3 = Renderer::getMainRenderer().addVertexToMesh(meshID, p3, normal, 0.5f, 0.5f);
		v4 = Renderer::getMainRenderer().addVertexToMesh(meshID, p4, normal, 0.0f, 0.5f);

		Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v2, v3);
		Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v3, v4);
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}

	//Right
	if ((x != CHUNK_SIZE - 1 && !(blocks[indexOfBlockAt(x + 1, y, z)]->isDrawn())) || x == CHUNK_SIZE - 1) {
		normal = vec3(1, 0, 0);

		v2 = Renderer::getMainRenderer().addVertexToMesh(meshID, p2, normal, 0.0f, 0.0f);
		v3 = Renderer::getMainRenderer().addVertexToMesh(meshID, p3, normal, 0.0f, 0.5f);
		v6 = Renderer::getMainRenderer().addVertexToMesh(meshID, p6, normal, 0.5f, 0.0f);
		v7 = Renderer::getMainRenderer().addVertexToMesh(meshID, p7, normal, 0.5f, 0.5f);

		Renderer::getMainRenderer().addTriangleToMesh(meshID, v2, v6, v7);
		Renderer::getMainRenderer().addTriangleToMesh(meshID, v2, v7, v3);
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}

	//Top
	if ((y != CHUNK_SIZE - 1 && !(blocks[indexOfBlockAt(x, y + 1, z)]->isDrawn())) || y == CHUNK_SIZE - 1) {
		normal = vec3(0, 1, 0);

		v3 = Renderer::getMainRenderer().addVertexToMesh(meshID, p3, normal, 0.5f, 0.5f);
		v4 = Renderer::getMainRenderer().addVertexToMesh(meshID, p4, normal, 0.0f, 0.5f);
		v7 = Renderer::getMainRenderer().addVertexToMesh(meshID, p7, normal, 0.5f, 1.0f);
		v8 = Renderer::getMainRenderer().addVertexToMesh(meshID, p8, normal, 0.0f, 1.0f);

		Renderer::getMainRenderer().addTriangleToMesh(meshID, v3, v7, v8);
		Renderer::getMainRenderer().addTriangleToMesh(meshID, v3, v8, v4);
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}

	//Bottom
	if ((y != 0 && !(blocks[indexOfBlockAt(x, y - 1, z)]->isDrawn())) || y == 0) {
		normal = vec3(0, -1, 0);

		v1 = Renderer::getMainRenderer().addVertexToMesh(meshID, p1, normal, 0.5f, 1.0f);
		v2 = Renderer::getMainRenderer().addVertexToMesh(meshID, p2, normal, 1.0f, 1.0f);
		v5 = Renderer::getMainRenderer().addVertexToMesh(meshID, p5, normal, 0.5f, 0.5f);
		v6 = Renderer::getMainRenderer().addVertexToMesh(meshID, p6, normal, 1.0f, 0.5f);

		Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v5, v6);
		Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v6, v2);
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}

	//Left
	if ((x != 0 && !(blocks[indexOfBlockAt(x - 1, y, z)]->isDrawn())) || x == 0) {
		normal = vec3(-1, 0, 0);

		v1 = Renderer::getMainRenderer().addVertexToMesh(meshID, p1, normal, 0.5f, 0.0f);
		v4 = Renderer::getMainRenderer().addVertexToMesh(meshID, p4, normal, 0.5f, 0.5f);
		v5 = Renderer::getMainRenderer().addVertexToMesh(meshID, p5, normal, 0.0f, 0.0f);
		v8 = Renderer::getMainRenderer().addVertexToMesh(meshID, p8, normal, 0.0f, 0.5f);

		Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v4, v8);
		Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v8, v5);
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}

	//Back
	if ((z != 0 && !(blocks[indexOfBlockAt(x, y, z - 1)]->isDrawn())) || z == 0) {
		normal = vec3(0, 0, -1);

		v5 = Renderer::getMainRenderer().addVertexToMesh(meshID, p5, normal, 0.5f, 0.0f);
		v6 = Renderer::getMainRenderer().addVertexToMesh(meshID, p6, normal, 0.0f, 0.0f);
		v7 = Renderer::getMainRenderer().addVertexToMesh(meshID, p7, normal, 0.0f, 0.5f);
		v8 = Renderer::getMainRenderer().addVertexToMesh(meshID, p8, normal, 0.5f, 0.5f);

		Renderer::getMainRenderer().addTriangleToMesh(meshID, v5, v8, v7);
		Renderer::getMainRenderer().addTriangleToMesh(meshID, v5, v7, v6);
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}
}

int Chunk::indexOfBlockAt(int x, int y, int z) {
	return (x * CHUNK_SIZE * CHUNK_SIZE) + (y * CHUNK_SIZE) + z;
}

bool Chunk::isLoaded() {
	return loaded;
}

void Chunk::draw(mat4 * viewMatrix) {
	shaderProgram.useProgram();
	Texture::stoneTexture->useTexture();

	mat4 modelMatrix = translate(chunkPosition);

	shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
	shaderProgram.setUniform("viewMatrix", viewMatrix, 1);
	shaderProgram.setUniform("projectionMatrix", Renderer::getProjectionMatrix(), 1);

	shaderProgram.setUniform("testColor", &testColor, 1);

	Renderer::getMainRenderer().renderMesh(meshID);

	Texture::unbindTextures();
}

void Chunk::setTestColor(float r, float g, float b) {
	testColor = glm::vec3(r, g, b);
}

