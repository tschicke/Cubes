/*
 * ChunkManager.cpp
 *
 *  Created on: Mar 17, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "Player.h"

#include "ChunkManager.h"

ChunkManager::ChunkManager() {
	mainPlayer = NULL;
}

ChunkManager::ChunkManager(Player * mainPlayer) {
	this->mainPlayer = mainPlayer;
	loadChunks(); //Temp?
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
	loadChunks();
	unloadChunks();

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
		chunk->draw(mainPlayer);
	}
}

Chunk * ChunkManager::getChunkWithCoordinate(int x, int y, int z) {
	Chunk * returnChunk = NULL;
	std::vector<Chunk *>::iterator iterator;
	for (iterator = chunks.begin(); iterator != chunks.end(); iterator++) { //TODO add max limit per frame
		Chunk *chunk = *iterator;
		glm::vec3 chunkPos = chunk->getChunkPos();
		bool inChunk = (x >= chunkPos.x && x < (chunkPos.x + Chunk::CHUNK_SIZE)) && (y >= chunkPos.y && y < (chunkPos.y + Chunk::CHUNK_SIZE))
				&& (z >= chunkPos.z && z < (chunkPos.z + Chunk::CHUNK_SIZE));
		if (inChunk) {
			returnChunk = chunk;
			break;
		}
	}
	return returnChunk;
}

void ChunkManager::loadChunks() { //TODO add max limit for chunks loaded per frame
	for (int x = (mainPlayer->getPosition().x / Chunk::CHUNK_SIZE - 1); x < (mainPlayer->getPosition().x / Chunk::CHUNK_SIZE) + 1; ++x) { //TODO should this be done this way? or should flags be used
		for (int y = (mainPlayer->getPosition().y / Chunk::CHUNK_SIZE) - 2; y < (mainPlayer->getPosition().y / Chunk::CHUNK_SIZE) + 0; ++y) {
			for (int z = (mainPlayer->getPosition().z / Chunk::CHUNK_SIZE) - 1; z < (mainPlayer->getPosition().z / Chunk::CHUNK_SIZE) + 1; ++z) {
				Chunk * currentChunk = getChunkWithCoordinate(x * Chunk::CHUNK_SIZE, y * Chunk::CHUNK_SIZE, z * Chunk::CHUNK_SIZE);
				if ((currentChunk != NULL && !(currentChunk->isLoaded())) || !currentChunk) {
					addChunk(x * Chunk::CHUNK_SIZE, y * Chunk::CHUNK_SIZE, z * Chunk::CHUNK_SIZE, 1, 1, 1);
					return;
				}
			}
		}
	}
}

void ChunkManager::unloadChunks() {
	std::vector<Chunk *>::iterator iterator;
	for (iterator = chunks.begin(); iterator != chunks.end(); iterator++) { //TODO add max limit per frame
		Chunk *chunk = *iterator;
		int maxDistSquared = 10 * 10 * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE;
		float xDistSquared = (chunk->getChunkPos().x - mainPlayer->getPosition().x) * (chunk->getChunkPos().x - mainPlayer->getPosition().x);
		float yDistSquared = (chunk->getChunkPos().y - mainPlayer->getPosition().y) * (chunk->getChunkPos().y - mainPlayer->getPosition().y);
		float zDistSquared = (chunk->getChunkPos().z - mainPlayer->getPosition().z) * (chunk->getChunkPos().z - mainPlayer->getPosition().z);
//		std::cout << xDistSquared / (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE) << ", " << zDistSquared / (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE)<< '\n';
		if (xDistSquared > maxDistSquared || yDistSquared > maxDistSquared || zDistSquared > maxDistSquared) {
//			chunk->deleteChunk()
			delete chunk;
			chunks.erase(iterator);
		}
	}
}
