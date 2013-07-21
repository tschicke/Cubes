/*
 * SelectedBlock.h
 *
 *  Created on: Jun 17, 2013
 *      Author: Tyler
 */

#ifndef SELECTEDBLOCK_H_
#define SELECTEDBLOCK_H_

#include <glm/glm.hpp>

#include "BaseRenderer.h"

class Block;
class Player;

enum Face /*: char*/{
	face_back, face_front, face_left, face_right, face_bottom, face_top, face_nocollision
};

class SelectedBlock : public BaseRenderer {
public:
	SelectedBlock();
	SelectedBlock(int x, int y, int z, Block * block, Face face, Player * parentPlayer);
	virtual ~SelectedBlock();

	void init(int x, int y, int z, Block * block, Face face, Player * parentPlayer);

	void set(int x, int y, int z, Block * block, Face face);

	int x, y, z;
	Block * block;

	int face;

	glm::vec3 getAddBlockPosition();

	void render();

private:
	void loadModel();

	int numVertices, numVerticesToDraw;
	bool modelMatNeedsUpdate;

	Player * parentPlayer;
};

#endif /* SELECTEDBLOCK_H_ */
