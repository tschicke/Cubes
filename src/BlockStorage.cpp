/*
 * ChunkStorage.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Tyler
 */

#include "BlockStorage.h"

#include <iostream>

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
	for(int i = 0; i < blockArrayLength; ++i){
		blockArray[i] = NULL;
	}
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
			blockArray[i] = NULL;
		}

		delete[] blockArray;
		blockArray = NULL;
	}
}

bool BlockStorage::hasParentChunk() {
	return parentChunkLoaded;
}

int BlockStorage::getBlockArrayLength() {
	return blockArrayLength;
}

Block** BlockStorage::getBlockArray() {
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

void BlockStorage::markBlocksAroundBlockDirty(int x, int y, int z) {
	int chunkSize = Chunk::CHUNK_SIZE;
	blockArray[(x - 1) * chunkSize * chunkSize + y * chunkSize + z]->setNeedsFaceUpdate(true);//TODO add x == 0, x == chunkSize - 1 checks
	blockArray[(x + 1) * chunkSize * chunkSize + y * chunkSize + z]->setNeedsFaceUpdate(true);
	blockArray[x * chunkSize * chunkSize + (y - 1) * chunkSize + z]->setNeedsFaceUpdate(true);
	blockArray[x * chunkSize * chunkSize + (y + 1) * chunkSize + z]->setNeedsFaceUpdate(true);
	blockArray[x * chunkSize * chunkSize + y * chunkSize + (z - 1)]->setNeedsFaceUpdate(true);
	blockArray[x * chunkSize * chunkSize + y * chunkSize + (z + 1)]->setNeedsFaceUpdate(true);
}
