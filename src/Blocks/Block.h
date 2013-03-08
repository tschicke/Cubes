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
	blockType_Air,
	blockType_Default
};

class Block {
public:
	Block();
	Block(BlockType type);
	virtual ~Block();

	void setDrawn(bool drawn);
	bool isDrawn();

	void setBlockType(BlockType type);
	BlockType getBlockType();
protected:
	bool drawn;
	BlockType blockType;
};

#endif /* CUBE_H_ */
