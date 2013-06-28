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
	loaded = false;
	blockStorage = NULL;
}

void Chunk::init(int startX, int startY, int startZ) {
	chunkPosition = glm::vec3(startX, startY, startZ);

	blockStorage = new BlockStorage(this);

	ts::TerrainGenerator generator;

	generator.generateChunk(startX, startY, startZ, blockStorage->getBlockArray());

	loaded = true;

	chunkRenderer = ChunkRenderer(chunkPosition.x, chunkPosition.y, chunkPosition.z, this);
}

Chunk::~Chunk() {
	chunkRenderer.deleteBuffers();

	delete blockStorage;
	blockStorage = NULL;
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
	return blockStorage->getBlockArray()[indexOfBlockAt(x, y, z)];
}

void Chunk::update(time_t dt) {
	chunkRenderer.update(dt);
}

void Chunk::addBlockOfTypeAtPosition(int x, int y, int z, BlockType blockType) {
	x %= CHUNK_SIZE;
	x = (x < 0 ? x + CHUNK_SIZE : x);
	y %= CHUNK_SIZE;
	y = (y < 0 ? y + CHUNK_SIZE : y);
	z %= CHUNK_SIZE;
	z = (z < 0 ? z + CHUNK_SIZE : z);

	int blockIndex = indexOfBlockAt(x, y, z);
	if (blockStorage->getBlockArray()[blockIndex]->getBlockType() == blockType_Air) {
		blockStorage->getBlockArray()[blockIndex] = Block::getBlockOfType(blockType);
		chunkRenderer.updateBlockAtPosition(x, y, z);
	}
}

void Chunk::removeBlockAtPosition(int x, int y, int z) {
	x %= CHUNK_SIZE;
	x = (x < 0 ? x + CHUNK_SIZE : x);
	y %= CHUNK_SIZE;
	y = (y < 0 ? y + CHUNK_SIZE : y);
	z %= CHUNK_SIZE;
	z = (z < 0 ? z + CHUNK_SIZE : z);

	int blockIndex = indexOfBlockAt(x, y, z);
	if (blockStorage->getBlockArray()[blockIndex]->getBlockType() != blockType_Air) {
		blockStorage->getBlockArray()[blockIndex] = Block::getBlockOfType(blockType_Air);
		chunkRenderer.markDirty();
	}
}

int Chunk::indexOfBlockAt(int x, int y, int z) {
	return (x * CHUNK_SIZE * CHUNK_SIZE) + (y * CHUNK_SIZE) + z;
}

bool Chunk::isLoaded() {
	return loaded;
}

void Chunk::draw(Player * player) {
	chunkRenderer.render(player);

}

void Chunk::setTestColor(float r, float g, float b) {
	testColor = glm::vec3(r, g, b);
}

