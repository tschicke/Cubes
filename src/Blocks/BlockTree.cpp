/*
 * BlockTree.cpp
 *
 *  Created on: May 18, 2013
 *      Author: Tyler
 */

#include "BlockTree.h"

BlockTree::BlockTree() {
}

BlockTree::~BlockTree() {
}

bool BlockTree::isDrawn(){
	return true;
}

BlockType BlockTree::getBlockType(){
	return blockType_Tree;
}

bool BlockTree::isSolid() {
	return true;
}
