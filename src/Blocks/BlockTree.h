/*
 * BlockTree.h
 *
 *  Created on: May 18, 2013
 *      Author: Tyler
 */

#ifndef BLOCKTREE_H_
#define BLOCKTREE_H_

#include "Block.h"

class BlockTree: public Block {
public:
	BlockTree();
	virtual ~BlockTree();

	bool isDrawn();
	bool isSolid();
	BlockType getBlockType();

	float getBaseTextureX();
	float getBaseTextureY();
};

#endif /* BLOCKTREE_H_ */
