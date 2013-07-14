/*
 * Cube.h
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */

#ifndef CUBE_H_
#define CUBE_H_

#include <glm/glm.hpp>

#include "../SelectedBlock.h"

enum BlockType/* : char*/{
	blockType_Grass,
	blockType_Dirt,
	blockType_Stone,
	blockType_Tree,
	blockType_Brick,
	blockType_Air,
	blockType_Null,
	numBlockTypes
};

class Block {
public:
	Block();
	Block(BlockType type);
	virtual ~Block();

	virtual bool isDrawn();
	virtual bool isSolid();
	virtual BlockType getBlockType();

	static const float cubeSize = 1.f;

	virtual float getBaseTextureX();
	virtual float getBaseTextureY();

	Face raytrace(int x, int y, int z, glm::vec3 startVec, glm::vec3 endVec);

	static Block * getBlockOfType(BlockType type);
protected:
	static Block * blocks[numBlockTypes];
};

#endif /* CUBE_H_ */
