/*
 * Cube.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */

#include "Block.h"

#include <iostream>

#include "../SpriteSheet.h"

Block::Block() {
	flagNeedsFaceUpdate = false;
}

Block::Block(BlockType type){
	flagNeedsFaceUpdate = false;
}

Block::~Block() {
}

bool Block::isDrawn(){
	return true;
}

bool Block::isSolid() {
	return false;
}

BlockType Block::getBlockType(){
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
