/*
 * BlockStone.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: Tyler
 */

#include "BlockStone.h"

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
