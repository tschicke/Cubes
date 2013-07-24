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
	blockArray = NULL;
	blockArrayLength = 0;
	loaded = false;
}

BlockStorage::BlockStorage(int width, int height, int depth) {
	loaded = false;
	init(width, height, depth);
}

void BlockStorage::init(int width, int height, int depth) {
	if(loaded){
		freeArray();
	}
	blockArrayLength = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE;
	blockArray = new Block *[blockArrayLength];
	for (int i = 0; i < blockArrayLength; ++i) {
		blockArray[i] = NULL;
	}
	loaded = true;
}

BlockStorage::~BlockStorage() {
	for (int i = 0; i < blockArrayLength; ++i) {
		blockArray[i] = NULL;
	}

	delete[] blockArray;
	blockArray = NULL;
}

int BlockStorage::getBlockArrayLength() {
	return blockArrayLength;
}

Block** BlockStorage::getBlockArray() {
	return blockArray;
}

void BlockStorage::freeArray() {
	for (int i = 0; i < blockArrayLength; ++i) {
		delete blockArray[i];
	}

	delete[] blockArray;

	loaded = false;
}
