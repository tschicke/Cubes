/*
 * BlockGrass.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: Tyler
 */

#include "BlockGrass.h"

#include "../SpriteSheet.h"

BlockGrass::BlockGrass() {
}

BlockGrass::~BlockGrass() {
}

bool BlockGrass::isDrawn(){
	return true;
}

BlockType BlockGrass::getBlockType(){
	return blockType_Grass;
}

bool BlockGrass::isSolid() {
	return true;
}

float BlockGrass::getBaseTextureX() {
	return 0;
}

float BlockGrass::getBaseTextureY() {
	return 0;
}
