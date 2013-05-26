/*
 * Cube.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */

#include "Block.h"

#include <iostream>

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

void Block::setNeedsFaceUpdate(bool flag) {
	flagNeedsFaceUpdate = flag;
}
