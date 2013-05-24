/*
 * ChunkStorage.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Tyler
 */

#include "BlockStorage.h"

#include "Chunk.h"

BlockStorage::BlockStorage() {
	init(NULL);
}

BlockStorage::BlockStorage(Chunk* parentChunk) {
	init(parentChunk);
}

void BlockStorage::init(Chunk * parentChunk) {
	blockArrayLength = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE;
	blockArray = new Block *[blockArrayLength];
	if (parentChunk != NULL) {
		parentChunkLoaded = true;
	} else {
		parentChunkLoaded = false;
	}
	this->parentChunk = parentChunk;
}

BlockStorage::~BlockStorage() {
	if (parentChunkLoaded) {
		for (int i = 0; i < blockArrayLength; ++i) {
			delete blockArray[i];
		}

		delete[] blockArray;
	}
}

bool BlockStorage::hasParentChunk() {
	return parentChunkLoaded;
}

int BlockStorage::getBlockArrayLength() {
	return blockArrayLength;
}

Block** BlockStorage::getBlockArrayAddress() {
	return blockArray;
}

void BlockStorage::setParentChunk(Chunk* parentChunk) {
	if (parentChunk != NULL) {
		this->parentChunk = parentChunk;
		parentChunkLoaded = true;
	}
}

void BlockStorage::freeArray() {
	if (parentChunkLoaded) {
		for (int i = 0; i < blockArrayLength; ++i) {
			delete blockArray[i];
		}

		delete[] blockArray;
	}
}
