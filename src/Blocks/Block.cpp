/*
 * Cube.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */

#include "Block.h"

#include <iostream>

#include "../BlockTypes.h"

#include "../SpriteSheet.h"

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include "../VectorHelper.h"

Block::Block() {
	flagNeedsFaceUpdate = false;
}

Block::Block(BlockType type) {
	flagNeedsFaceUpdate = false;
}

Block::~Block() {
}

bool Block::isDrawn() {
	return true;
}

bool Block::isSolid() {
	return false;
}

BlockType Block::getBlockType() {
	return blockType_Null;
}

bool Block::needsFaceUpdate() {
	return flagNeedsFaceUpdate;
}

float Block::getBaseTextureX() {
	return 3 * (2 * ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getWidth());
}

float Block::getBaseTextureY() {
	return 3 * (2 * ts::SpriteSheet::defaultSpriteSheet->getElementSizePixels() / (float) ts::SpriteSheet::defaultSpriteSheet->getHeight());
}

void Block::setNeedsFaceUpdate(bool flag) {
	flagNeedsFaceUpdate = flag;
}

Face Block::raytrace(int x, int y, int z, glm::vec3 startVec, glm::vec3 endVec) {
	glm::vec3 xMinVec = VectorHelper::getIntermediateWithXValue(startVec, endVec, x);
	glm::vec3 xMaxVec = VectorHelper::getIntermediateWithXValue(startVec, endVec, x + cubeSize);
	glm::vec3 yMinVec = VectorHelper::getIntermediateWithYValue(startVec, endVec, y);
	glm::vec3 yMaxVec = VectorHelper::getIntermediateWithYValue(startVec, endVec, y + cubeSize);
	glm::vec3 zMinVec = VectorHelper::getIntermediateWithZValue(startVec, endVec, z);
	glm::vec3 zMaxVec = VectorHelper::getIntermediateWithZValue(startVec, endVec, z + cubeSize);

	if (!VectorHelper::isPointInYZBounds(glm::vec3(x, y, z), glm::vec3(x, y + cubeSize, z + cubeSize), xMinVec)) {
		xMinVec = VectorHelper::NULL_VECTOR;
	}
	if (!VectorHelper::isPointInYZBounds(glm::vec3(x + cubeSize, y, z), glm::vec3(x + cubeSize, y + cubeSize, z + cubeSize), xMaxVec)) {
		xMaxVec = VectorHelper::NULL_VECTOR;
	}
	if (!VectorHelper::isPointInXZBounds(glm::vec3(x, y, z), glm::vec3(x + cubeSize, y, z + cubeSize), yMinVec)) {
		yMinVec = VectorHelper::NULL_VECTOR;
	}
	if (!VectorHelper::isPointInXZBounds(glm::vec3(x, y + cubeSize, z), glm::vec3(x + cubeSize, y + cubeSize, z + cubeSize), yMaxVec)) {
		yMaxVec = VectorHelper::NULL_VECTOR;
	}
	if (!VectorHelper::isPointInXYBounds(glm::vec3(x, y, z), glm::vec3(x + cubeSize, y + cubeSize, z), zMinVec)) {
		zMinVec = VectorHelper::NULL_VECTOR;
	}
	if (!VectorHelper::isPointInXYBounds(glm::vec3(x, y, z + cubeSize), glm::vec3(x + cubeSize, y + cubeSize, z + cubeSize), zMaxVec)) {
		zMaxVec = VectorHelper::NULL_VECTOR;
	}


	glm::vec3 collisionPoint = VectorHelper::NULL_VECTOR;

	if (xMinVec != VectorHelper::NULL_VECTOR && (collisionPoint == VectorHelper::NULL_VECTOR || glm::distance2(startVec, xMinVec) < glm::distance2(startVec, collisionPoint))) {
		collisionPoint = xMinVec;
	}
	if (xMaxVec != VectorHelper::NULL_VECTOR && (collisionPoint == VectorHelper::NULL_VECTOR || glm::distance2(startVec, xMaxVec) < glm::distance2(startVec, collisionPoint))) {
		collisionPoint = xMaxVec;
	}
	if (yMinVec != VectorHelper::NULL_VECTOR && (collisionPoint == VectorHelper::NULL_VECTOR || glm::distance2(startVec, yMinVec) < glm::distance2(startVec, collisionPoint))) {
		collisionPoint = yMinVec;
	}
	if (yMaxVec != VectorHelper::NULL_VECTOR && (collisionPoint == VectorHelper::NULL_VECTOR || glm::distance2(startVec, yMaxVec) < glm::distance2(startVec, collisionPoint))) {
		collisionPoint = yMaxVec;
	}
	if (zMinVec != VectorHelper::NULL_VECTOR && (collisionPoint == VectorHelper::NULL_VECTOR || glm::distance2(startVec, zMinVec) < glm::distance2(startVec, collisionPoint))) {
		collisionPoint = zMinVec;
	}
	if (zMaxVec != VectorHelper::NULL_VECTOR && (collisionPoint == VectorHelper::NULL_VECTOR || glm::distance2(startVec, zMaxVec) < glm::distance2(startVec, collisionPoint))) {
		collisionPoint = zMaxVec;
	}

	Face face = face_nocollision;
	if (collisionPoint != VectorHelper::NULL_VECTOR) {
		if(collisionPoint == xMinVec){
			face = face_left;
		} else if(collisionPoint == xMaxVec){
			face = face_right;
		} else if(collisionPoint == yMinVec){
			face = face_bottom;
		} else if(collisionPoint == yMaxVec){
			face = face_top;
		} else if(collisionPoint == zMinVec){
			face = face_back;
		} else if(collisionPoint == zMaxVec){
			face = face_front;
		}
	}

	return face;
}

Block* Block::getBlockOfType(BlockType blockType) {
	Block * returnBlock = NULL;
	switch (blockType) {
	case blockType_Grass:
		returnBlock = new BlockGrass;
		break;
	case blockType_Dirt:
		returnBlock = new BlockDirt;
		break;
	case blockType_Stone:
		returnBlock = new BlockStone;
		break;
	case blockType_Tree:
		returnBlock = new BlockTree;
		break;
	case blockType_Air:
		returnBlock = new BlockAir;
		break;
	default:
		returnBlock = new Block;
		break;
	}

	return returnBlock;
}
