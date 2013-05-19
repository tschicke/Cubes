/*
 * BlockGrass.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "BlockGrass.h"

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
