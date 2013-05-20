/*
 * Chunk.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */
#include <iostream>

#include "Chunk.h"
#include "Shader.h"
#include "SpriteSheet.h"
#include "Renderer.h"
#include "Player.h"

#include "TerrainGenerator.h"

#include <gl/glew.h>//Only for GL_VERTEX_SHADER and GL_FRAGMENT_SHADER, get them from somewhere else
#include <glm/glm.hpp>//Temp??
#include <glm/gtx/transform.hpp>//Temp??
using namespace glm;
//Temp??

Chunk::Chunk() {
	blocks = NULL;
	loaded = false;
	blockStorage = NULL;
}

void Chunk::init(int startX, int startY, int startZ) {
	chunkPosition = glm::vec3(startX, startY, startZ);
	meshID.setColorType(ColorType_Texture);

	Renderer::getMainRenderer().createMesh(&meshID);

	blocks = new Block*[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

	ts::TerrainGenerator generator;

	BlockType *blockTypes = new BlockType[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	generator.generateChunk(startX, startY, startZ, blockTypes);

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
//				std::cout << blockTypes[indexOfBlockAt(x, y, z)] << '\n';
				if (blockTypes[indexOfBlockAt(x, y, z)] == blockType_Dirt) {
					blocks[indexOfBlockAt(x, y, z)] = new BlockDirt;
				} else if (blockTypes[indexOfBlockAt(x, y, z)] == blockType_Grass) {
					blocks[indexOfBlockAt(x, y, z)] = new BlockGrass;
				} else if (blockTypes[indexOfBlockAt(x, y, z)] == blockType_Tree) {
					blocks[indexOfBlockAt(x, y, z)] = new BlockTree;
				} else {
					blocks[indexOfBlockAt(x, y, z)] = new BlockAir;
				}
			}
		}
	}

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				Block * block = blocks[indexOfBlockAt(x, y, z)];
//				if (block->isDrawn()) {
					createCube((x * Block::cubeSize), (y * Block::cubeSize), (z * Block::cubeSize)); //FIXME fix occlusion culling between chunks, and organize it better
//				} else {
//					Renderer::getMainRenderer().addNullCube(meshID);
//				}
			}
		}
	}

	delete blockTypes;

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





	//New Stuff;
	blockStorage = new BlockStorage(this);
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

	//New Stuff
	blockStorage->freeArray();
	delete blockStorage;
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

	int vert1, vert2, vert3, vert4, vert5, vert6, vert7, vert8;

	int tileX, tileY;
	Block * currentBlock = blocks[indexOfBlockAt(x, y, z)];
	if (currentBlock->getBlockType() == blockType_Grass) {
		tileX = 0;
		tileY = 0;
	} else if (currentBlock->getBlockType() == blockType_Stone) {
		tileX = 1;
		tileY = 0;
	} else if (currentBlock->getBlockType() == blockType_Dirt) {
		tileX = 2;
		tileY = 0;
	} else if (currentBlock->getBlockType() == blockType_Tree) {
		tileX = 3;
		tileY = 0;
	}

	ts::SpriteSheet * spriteSheet = ts::SpriteSheet::defaultSpriteSheet; //TODO dont automatically use default spritesheet

	int texElementSizePixels = spriteSheet->getElementSizePixels();
	float textureElementWidth = texElementSizePixels / (float) spriteSheet->getWidth();
	float textureElementHeight = texElementSizePixels / (float) spriteSheet->getHeight();
	float u1 = (texElementSizePixels * tileX * 2) / (float) spriteSheet->getWidth(), u2 = ((texElementSizePixels * tileX * 2) + texElementSizePixels) / (float) spriteSheet->getWidth();
	float v1 = (texElementSizePixels * tileY * 2) / (float) spriteSheet->getWidth(), v2 = ((texElementSizePixels * tileY * 2) + texElementSizePixels) / (float) spriteSheet->getWidth();

	//Front
	if ((z != CHUNK_SIZE - 1 && !(blocks[indexOfBlockAt(x, y, z + 1)]->isDrawn())) || z == CHUNK_SIZE - 1) {
		normal = vec3(0, 0, 1);

		vert1 = Renderer::getMainRenderer().addVertexToMesh(meshID, p1, normal, u1, v2 + textureElementWidth);
		vert2 = Renderer::getMainRenderer().addVertexToMesh(meshID, p2, normal, u1 + textureElementWidth, v2 + textureElementWidth);
		vert3 = Renderer::getMainRenderer().addVertexToMesh(meshID, p3, normal, u1 + textureElementWidth, v2);
		vert4 = Renderer::getMainRenderer().addVertexToMesh(meshID, p4, normal, u1, v2);

		if (currentBlock->isDrawn()) {
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert1, vert2, vert3);
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert1, vert3, vert4);
		}
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}

	//Right
	if ((x != CHUNK_SIZE - 1 && !(blocks[indexOfBlockAt(x + 1, y, z)]->isDrawn())) || x == CHUNK_SIZE - 1) {
		normal = vec3(1, 0, 0);

		vert2 = Renderer::getMainRenderer().addVertexToMesh(meshID, p2, normal, u1, v2 + textureElementHeight);
		vert3 = Renderer::getMainRenderer().addVertexToMesh(meshID, p3, normal, u1, v2);
		vert6 = Renderer::getMainRenderer().addVertexToMesh(meshID, p6, normal, u1 + textureElementWidth, v2 + textureElementHeight);
		vert7 = Renderer::getMainRenderer().addVertexToMesh(meshID, p7, normal, u1 + textureElementWidth, v2);

		if (currentBlock->isDrawn()) {
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert2, vert6, vert7);
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert2, vert7, vert3);
		}
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}

	//Top
	if ((y != CHUNK_SIZE - 1 && !(blocks[indexOfBlockAt(x, y + 1, z)]->isDrawn())) || y == CHUNK_SIZE - 1) {
		normal = vec3(0, 1, 0);

		vert3 = Renderer::getMainRenderer().addVertexToMesh(meshID, p3, normal, u1 + textureElementWidth, v1);
		vert4 = Renderer::getMainRenderer().addVertexToMesh(meshID, p4, normal, u1, v1);
		vert7 = Renderer::getMainRenderer().addVertexToMesh(meshID, p7, normal, u1 + textureElementWidth, v1 + textureElementHeight);
		vert8 = Renderer::getMainRenderer().addVertexToMesh(meshID, p8, normal, u1, v1 + textureElementHeight);

		if (currentBlock->isDrawn()) {
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert3, vert7, vert8);
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert3, vert8, vert4);
		}
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}

	//Bottom
	if ((y != 0 && !(blocks[indexOfBlockAt(x, y - 1, z)]->isDrawn())) || y == 0) {
		normal = vec3(0, -1, 0);

		vert1 = Renderer::getMainRenderer().addVertexToMesh(meshID, p1, normal, u2, v1 + textureElementHeight);
		vert2 = Renderer::getMainRenderer().addVertexToMesh(meshID, p2, normal, u2 + textureElementWidth, v1 + textureElementHeight);
		vert5 = Renderer::getMainRenderer().addVertexToMesh(meshID, p5, normal, u2, v1);
		vert6 = Renderer::getMainRenderer().addVertexToMesh(meshID, p6, normal, u2 + textureElementWidth, v1);

		if (currentBlock->isDrawn()) {
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert1, vert5, vert6);
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert1, vert6, vert2);
		}
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}

	//Left
	if ((x != 0 && !(blocks[indexOfBlockAt(x - 1, y, z)]->isDrawn())) || x == 0) {
		normal = vec3(-1, 0, 0);

		vert1 = Renderer::getMainRenderer().addVertexToMesh(meshID, p1, normal, u1 + textureElementWidth, v2 + textureElementHeight);
		vert4 = Renderer::getMainRenderer().addVertexToMesh(meshID, p4, normal, u1 + textureElementWidth, v2);
		vert5 = Renderer::getMainRenderer().addVertexToMesh(meshID, p5, normal, u1, v2 + textureElementHeight);
		vert8 = Renderer::getMainRenderer().addVertexToMesh(meshID, p8, normal, u1, v2);

		if (currentBlock->isDrawn()) {
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert1, vert4, vert8);
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert1, vert8, vert5);
		}
	} else {
//		Renderer::getMainRenderer().addNullQuad(meshID);
	}

	//Back
	if ((z != 0 && !(blocks[indexOfBlockAt(x, y, z - 1)]->isDrawn())) || z == 0) {
		normal = vec3(0, 0, -1);

		vert5 = Renderer::getMainRenderer().addVertexToMesh(meshID, p5, normal, u1 + textureElementWidth, v2 + textureElementHeight);
		vert6 = Renderer::getMainRenderer().addVertexToMesh(meshID, p6, normal, u1, v2 + textureElementHeight);
		vert7 = Renderer::getMainRenderer().addVertexToMesh(meshID, p7, normal, u1, v2);
		vert8 = Renderer::getMainRenderer().addVertexToMesh(meshID, p8, normal, u1 + textureElementWidth, v2);

		if (currentBlock->isDrawn()) {
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert5, vert8, vert7);
			Renderer::getMainRenderer().addTriangleToMesh(meshID, vert5, vert7, vert6);
		}
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

void Chunk::draw(Player * player) {
	shaderProgram.useProgram();
	ts::SpriteSheet::defaultSpriteSheet->useTexture();

	mat4 modelMatrix = translate(chunkPosition);

	shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
	shaderProgram.setUniform("viewMatrix", player->getCameraViewMatrix(), 1);
	shaderProgram.setUniform("projectionMatrix", Renderer::getProjectionMatrix(), 1);

	shaderProgram.setUniform("testColor", &testColor, 1);

	Renderer::getMainRenderer().renderMesh(meshID);

	Texture::unbindTextures();


	//New Stuff

//	chunkRenderer.render(player);
}

void Chunk::setTestColor(float r, float g, float b) {
	testColor = glm::vec3(r, g, b);
}

