/*
 * ChunkStorage.h
 *
 *  Created on: May 11, 2013
 *      Author: Tyler
 */

#ifndef CHUNKSTORAGE_H_
#define CHUNKSTORAGE_H_

#include "BlockTypes.h"

class BlockStorage {
public:
	BlockStorage();
	virtual ~BlockStorage();

	bool isLoaded();
	int getBlockArrayLength();
	Block** getBlockArrayAddress();

private:
	Block ** blockArray;
	int blockArrayLength;

	bool loaded;
};

#endif /* CHUNKSTORAGE_H_ */
