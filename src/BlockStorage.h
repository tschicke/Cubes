/*
 * ChunkStorage.h
 *
 *  Created on: May 11, 2013
 *      Author: Tyler
 */

#ifndef BLOCKSTORAGE_H_
#define BLOCKSTORAGE_H_

#include "BlockTypes.h"

class BlockStorage {
public:
	BlockStorage();
	BlockStorage(int width, int height, int depth);
	virtual ~BlockStorage();

	void init(int width, int height, int depth);

	int getBlockArrayLength();
	Block** getBlockArray();

	void freeArray();
private:
	BlockStorage(const BlockStorage& copy);
	BlockStorage& operator=(const BlockStorage& copy);

	Block ** blockArray;
	int blockArrayLength;

	bool loaded;
};

#endif /* BLOCKSTORAGE_H_ */
