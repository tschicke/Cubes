/*
 * BlockAir.h
 *
 *  Created on: Feb 15, 2013
 *      Author: Tyler
 */

#ifndef BLOCKAIR_H_
#define BLOCKAIR_H_

#include "Block.h"

class BlockAir: public Block {
public:
	BlockAir();
	virtual ~BlockAir();

	bool isDrawn();
	bool isSolid();
	BlockType getBlockType();
};

#endif /* BLOCKAIR_H_ */
