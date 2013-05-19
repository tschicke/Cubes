/*
 * BlockDirt.h
 *
 *  Created on: Feb 13, 2013
 *      Author: Tyler
 */

#ifndef BLOCKDIRT_H_
#define BLOCKDIRT_H_

#include "Block.h"

class BlockDirt: public Block {
public:
	BlockDirt();
	virtual ~BlockDirt();


	bool isDrawn();
	bool isSolid();
	BlockType getBlockType();
};

#endif /* BLOCKDIRT_H_ */
