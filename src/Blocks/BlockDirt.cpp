/*
 * BlockDirt.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: Tyler
 */

#include "BlockDirt.h"

#include "../SpriteSheet.h"

BlockDirt::BlockDirt() {
}

BlockDirt::~BlockDirt() {
}

bool BlockDirt::isDrawn(){
	return true;
}

bool BlockDirt::isSolid() {
	return true;
}

BlockType BlockDirt::getBlockType(){
	return blockType_Dirt;
}

float BlockDirt::getBaseTextureX() {
	return 2 * (2 * ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getWidth());
}

float BlockDirt::getBaseTextureY() {
	return 0;
}
