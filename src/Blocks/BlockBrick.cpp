/*
 * BlockBrick.cpp
 *
 *  Created on: Jul 13, 2013
 *      Author: Tyler
 */

#include "BlockBrick.h"

#include "../SpriteSheet.h"

BlockBrick::BlockBrick() {

}

BlockBrick::~BlockBrick() {
}

bool BlockBrick::isDrawn(){
	return true;
}

bool BlockBrick::isSolid() {
	return true;
}

BlockType BlockBrick::getBlockType(){
	return blockType_Brick;
}

float BlockBrick::getBaseTextureX() {
	return 0 * (2 * ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getWidth());
}

float BlockBrick::getBaseTextureY() {
	return 1 * (2 * ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getWidth());
}
