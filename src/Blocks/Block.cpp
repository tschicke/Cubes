/*
 * Cube.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */

#include "Block.h"

#include <iostream>

Block::Block() {
	blockType = blockType_Default;
	drawn = true;
}

Block::Block(BlockType type){
	blockType = type;
	drawn = true;
}

Block::~Block() {
}

bool Block::isDrawn(){
	return drawn;
}

void Block::setDrawn(bool d){
	drawn = d;
}

BlockType Block::getBlockType(){
	return blockType;
}
