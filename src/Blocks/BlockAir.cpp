/*
 * BlockAir.cpp
 *
 *  Created on: Feb 15, 2013
 *      Author: Tyler
 */

#include "BlockAir.h"

BlockAir::BlockAir() {
}

BlockAir::~BlockAir() {
}

bool BlockAir::isDrawn(){
	return false;
}

BlockType BlockAir::getBlockType(){
	return blockType_Air;
}

bool BlockAir::isSolid() {
	return false;
}
