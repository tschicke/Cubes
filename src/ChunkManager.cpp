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

void ChunkManager::addChunk(int x, int y, int z){
	Chunk *chunk = new Chunk;
	chunk->init(x, y, z);
	chunks.push_back(chunk);
}

void ChunkManager::deleteChuck(int index){
	delete chunks[index];
	chunks[index] = NULL;
}

void ChunkManager::update(time_t dt){
	std::vector<Chunk *>::iterator iterator;
	for(iterator = chunks.begin(); iterator != chunks.end(); iterator++){//TODO add max limit per frame
		Chunk *chunk = *iterator;
		chunk->update(dt);
	}
}

void ChunkManager::draw(glm::mat4 *viewMat){
	std::vector<Chunk *>::iterator iterator;
	for(iterator = chunks.begin(); iterator != chunks.end(); iterator++){//TODO add max limit per frame
		Chunk *chunk = *iterator;
		chunk->draw(viewMat);
	}
}

