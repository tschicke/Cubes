/*
 * ChunkStorage.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Tyler
 */

#include "ChunkStorage.h"

BlockStorage::BlockStorage() {
	blockArray = 0;
	loaded = false;
	arraySize = 0;
}

BlockStorage::BlockStorage(int chunkSize) {
	arraySize = chunkSize * chunkSize * chunkSize;
	blockArray = new Block *[arraySize];
	loaded = false;
}

BlockStorage::~BlockStorage() {
	if(loaded){
		for (int i = 0; i < arraySize; ++i){
			delete blockArray[i];
		}

		delete blockArray;
	}
}

bool BlockStorage::isLoaded() {
	return loaded;
}
