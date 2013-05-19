/*
 * Cube.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */

#include "Block.h"

#include <iostream>

Block::Block() {
}

Block::Block(BlockType type){
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
