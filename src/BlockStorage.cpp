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
	for (int i = 0; i < blockArrayLength; ++i) {
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

	if (x != 0) {
		Block * blockXM1 = blockArray[(x - 1) * chunkSize * chunkSize + y * chunkSize + z];
		if (blockXM1->isDrawn()) {
			blockXM1->setNeedsFaceUpdate(true);
		}
	}
	if (x != chunkSize - 1) {
		Block * blockXP1 = blockArray[(x + 1) * chunkSize * chunkSize + y * chunkSize + z];
		if (blockXP1->isDrawn()) {
			blockXP1->setNeedsFaceUpdate(true);
		}
	}
	if (y != 0) {
		Block * blockYM1 = blockArray[x * chunkSize * chunkSize + (y - 1) * chunkSize + z];
		if (blockYM1->isDrawn()) {
			blockYM1->setNeedsFaceUpdate(true);
		}
	}
	if (y != chunkSize - 1) {
		Block * blockYP1 = blockArray[x * chunkSize * chunkSize + (y + 1) * chunkSize + z];
		if (blockYP1->isDrawn()) {
			blockYP1->setNeedsFaceUpdate(true);
		}
	}
	if (z != 0) {
		Block * blockZM1 = blockArray[x * chunkSize * chunkSize + y * chunkSize + (z - 1)];
		if (blockZM1->isDrawn()) {
			blockZM1->setNeedsFaceUpdate(true);
		}
	}
	if (z != chunkSize - 1) {
		Block * blockZP1 = blockArray[x * chunkSize * chunkSize + y * chunkSize + (z + 1)];
		if (blockZP1->isDrawn()) {
			blockZP1->setNeedsFaceUpdate(true);
		}
	}
}
