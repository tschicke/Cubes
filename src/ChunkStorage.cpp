/*
 * ChunkStorage.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Tyler
 */

#include "ChunkStorage.h"

#include "Chunk.h"

BlockStorage::BlockStorage() {
	blockArrayLength = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE;
	blockArray = new Block *[blockArrayLength];
	loaded = false;
}

BlockStorage::~BlockStorage() {
	if (loaded) {
		for (int i = 0; i < blockArrayLength; ++i) {
			delete blockArray[i];
		}

		delete blockArray;
	}
}

bool BlockStorage::isLoaded() {
	return loaded;
}

int BlockStorage::getBlockArrayLength() {
	return blockArrayLength;
}

Block** BlockStorage::getBlockArrayAddress() {
	return blockArray;
}
