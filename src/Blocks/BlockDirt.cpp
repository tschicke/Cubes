/*
 * BlockDirt.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: Tyler
 */

#include "BlockDirt.h"

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
