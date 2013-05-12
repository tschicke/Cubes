/*
 * ChunkStorage.h
 *
 *  Created on: May 11, 2013
 *      Author: Tyler
 */

#ifndef CHUNKSTORAGE_H_
#define CHUNKSTORAGE_H_

#include "Blocks/Block.h"

class BlockStorage {
public:
	BlockStorage();
	BlockStorage(int chunkSize);
	virtual ~BlockStorage();

	bool isLoaded();

private:
	Block ** blockArray;
	int arraySize;

	bool loaded;
};

#endif /* CHUNKSTORAGE_H_ */
