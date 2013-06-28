/*
 * ChunkStorage.h
 *
 *  Created on: May 11, 2013
 *      Author: Tyler
 */

#ifndef BLOCKSTORAGE_H_
#define BLOCKSTORAGE_H_

#include "BlockTypes.h"

class Chunk;

class BlockStorage {
public:
	BlockStorage();
	BlockStorage(Chunk * parentChunk);
	virtual ~BlockStorage();

	void setParentChunk(Chunk * parentChunk);

	bool hasParentChunk();
	int getBlockArrayLength();
	Block** getBlockArray();

	void freeArray();
private:
	BlockStorage(const BlockStorage& copy);
	BlockStorage& operator=(const BlockStorage& copy);

	Block ** blockArray;
	int blockArrayLength;

	void init(Chunk * parentChunk);

	bool parentChunkLoaded;

	Chunk * parentChunk;
};

#endif /* BLOCKSTORAGE_H_ */
