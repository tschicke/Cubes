/*
 * Cube.h
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */

#ifndef CUBE_H_
#define CUBE_H_


enum BlockType{
	blockType_Grass,
	blockType_Dirt,
	blockType_Stone,
	blockType_Tree,
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
protected:
};

#endif /* CUBE_H_ */
