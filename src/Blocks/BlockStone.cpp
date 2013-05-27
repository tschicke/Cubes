/*
 * BlockStone.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: Tyler
 */

#include "BlockStone.h"

#include "../SpriteSheet.h"

BlockStone::BlockStone() {
}

BlockStone::~BlockStone() {
}

bool BlockStone::isDrawn(){
	return true;
}

BlockType BlockStone::getBlockType(){
	return blockType_Stone;
}

bool BlockStone::isSolid() {
	return true;
}

float BlockStone::getBaseTextureX() {
	return 1 * (2 * ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getWidth());
}

float BlockStone::getBaseTextureY() {
	return 0;
}
