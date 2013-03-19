/*
 * ChunkManager.cpp
 *
 *  Created on: Mar 17, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "ChunkManager.h"

ChunkManager::ChunkManager() {

}

ChunkManager::~ChunkManager() {
}

void ChunkManager::addChunk(int x, int y, int z, float r, float g, float b) {
	Chunk *chunk = new Chunk;
	chunk->init(x, y, z);
	chunk->setTestColor(r, g, b);
	chunks.push_back(chunk);
}

void ChunkManager::deleteChuck(int index) {
	delete chunks[index];
	chunks[index] = NULL;
}

void ChunkManager::update(time_t dt) {
	std::vector<Chunk *>::iterator iterator;
	for (iterator = chunks.begin(); iterator != chunks.end(); iterator++) { //TODO add max limit per frame
		Chunk *chunk = *iterator;
		chunk->update(dt);
	}
}

void ChunkManager::draw(glm::mat4 *viewMat) {
	std::vector<Chunk *>::iterator iterator;
	for (iterator = chunks.begin(); iterator != chunks.end(); iterator++) { //TODO add max limit per frame
		Chunk *chunk = *iterator;
		chunk->draw(viewMat);
	}
}

Chunk * ChunkManager::getChunkWithCoordinate(int x, int y, int z) {
	Chunk * returnChunk = NULL;
	std::vector<Chunk *>::iterator iterator;
	for (iterator = chunks.begin(); iterator != chunks.end(); iterator++) { //TODO add max limit per frame
		Chunk *chunk = *iterator;
		glm::vec3 chunkPos = chunk->getChunkPos();
		bool inChunk = (x > chunkPos.x && x < (chunkPos.x + Chunk::CHUNK_SIZE)) && (y > chunkPos.y && y < (chunkPos.y + Chunk::CHUNK_SIZE)) && (z > chunkPos.z && z < (chunkPos.z + Chunk::CHUNK_SIZE));
		if (inChunk) {
			returnChunk = chunk;
			break;
		}
	}
	return returnChunk;
}

