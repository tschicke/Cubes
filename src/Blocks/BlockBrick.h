/*
 * BlockBrick.h
 *
 *  Created on: Jul 13, 2013
 *      Author: Tyler
 */

#ifndef BLOCKBRICK_H_
#define BLOCKBRICK_H_

#include "Block.h"

class BlockBrick: public Block {
public:
	BlockBrick();
	virtual ~BlockBrick();

	bool isDrawn();
	bool isSolid();
	BlockType getBlockType();

	float getBaseTextureX();
	float getBaseTextureY();
};

#endif /* BLOCKBRICK_H_ */
