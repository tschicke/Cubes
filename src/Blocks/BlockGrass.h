/*
 * BlockGrass.h
 *
 *  Created on: Feb 13, 2013
 *      Author: Tyler
 */

#ifndef BLOCKGRASS_H_
#define BLOCKGRASS_H_

#include "Block.h"

class BlockGrass: public Block {
public:
	BlockGrass();
	virtual ~BlockGrass();

	bool isDrawn();
	bool isSolid();
	BlockType getBlockType();

	float getBaseTextureX();
	float getBaseTextureY();
protected:
};

#endif /* BLOCKGRASS_H_ */
