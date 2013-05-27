/*
 * BlockStone.h
 *
 *  Created on: Feb 13, 2013
 *      Author: Tyler
 */

#ifndef BLOCKSTONE_H_
#define BLOCKSTONE_H_

#include "Block.h"

class BlockStone: public Block {
public:
	BlockStone();
	virtual ~BlockStone();

	bool isDrawn();
	bool isSolid();
	BlockType getBlockType();

	float getBaseTextureX();
	float getBaseTextureY();
};

#endif /* BLOCKSTONE_H_ */
