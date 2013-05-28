/*
 * Cube.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */

#include "Block.h"

#include <iostream>

#include "../BlockTypes.h"

#include "../SpriteSheet.h"

Block::Block() {
	flagNeedsFaceUpdate = false;
}

Block::Block(BlockType type) {
	flagNeedsFaceUpdate = false;
}

Block::~Block() {
}

bool Block::isDrawn() {
	return true;
}

bool Block::isSolid() {
	return false;
}

BlockType Block::getBlockType() {
	return blockType_Null;
}

bool Block::needsFaceUpdate() {
	return flagNeedsFaceUpdate;
}

float Block::getBaseTextureX() {
	return 3 * (2 * ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getWidth());
}

float Block::getBaseTextureY() {
	return 3 * (2 * ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getHeight());
}

void Block::setNeedsFaceUpdate(bool flag) {
	flagNeedsFaceUpdate = flag;
}

Block* Block::getBlockOfType(BlockType blockType) {
	Block * returnBlock = NULL;
	switch (blockType) {
	case blockType_Grass:
		returnBlock = new BlockGrass;
		break;
	case blockType_Dirt:
		returnBlock = new BlockDirt;
		break;
	case blockType_Stone:
		returnBlock = new BlockStone;
		break;
	case blockType_Tree:
		returnBlock = new BlockTree;
		break;
	case blockType_Air:
		returnBlock = new BlockAir;
		break;
	default:
		returnBlock = new Block;
		break;
	}

	return returnBlock;
}
