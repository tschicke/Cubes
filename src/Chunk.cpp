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

#include <gl/glew.h>//Only for GL_VERTEX_SHADER and GL_FRAGMENT_SHADER, get them from somewhere else
#include <glm/glm.hpp>//Temp??
#include <glm/gtx/transform.hpp>//Temp??
using namespace glm;
//Temp??

Chunk::Chunk() {
	blockStorage = NULL;
	chunkState = initialize;
}

Chunk::Chunk(int x, int y, int z){
	blockStorage = new BlockStorage(this);
	chunkPosition = glm::vec3(x, y, z);

	chunkState = initialize;
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

void Chunk::setBlockTypeAtPosition(int x, int y, int z, BlockType type) {
	x %= CHUNK_SIZE;
	x = (x < 0 ? x + CHUNK_SIZE : x);
	y %= CHUNK_SIZE;
	y = (y < 0 ? y + CHUNK_SIZE : y);
	z %= CHUNK_SIZE;
	z = (z < 0 ? z + CHUNK_SIZE : z);

	int blockIndex = indexOfBlockAt(x, y, z);
	if(blockStorage->getBlockArray()[blockIndex] != NULL && blockStorage->getBlockArray()[blockIndex]->getBlockType() == type){
		return;
	}

	blockStorage->getBlockArray()[blockIndex] = Block::getBlockOfType(type);

	if(type != blockType_Air){
		chunkRenderer.markBlockAtPositionDirty(x, y, z);
	}

	setChunkState(rebuild);

	chunkRenderer.markIndicesDirty();
}

Chunk::State Chunk::getChunkState() {
	return chunkState;
}

void Chunk::setChunkState(State state) {
	chunkState = state;
}

int Chunk::indexOfBlockAt(int x, int y, int z) {
	return (x * CHUNK_SIZE * CHUNK_SIZE) + (y * CHUNK_SIZE) + z;
}

void Chunk::draw(Player * player) {
	chunkRenderer.render(player);

}

void Chunk::setTestColor(float r, float g, float b) {
	testColor = glm::vec3(r, g, b);
}

