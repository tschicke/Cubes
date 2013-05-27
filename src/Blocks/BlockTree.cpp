/*
 * BlockTree.cpp
 *
 *  Created on: May 18, 2013
 *      Author: Tyler
 */

#include "BlockTree.h"

#include "../SpriteSheet.h"

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

float BlockTree::getBaseTextureX() {
	return 3 * (2 * ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getWidth());
}

float BlockTree::getBaseTextureY() {
	return 0;
}
