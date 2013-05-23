/*
 * ChunkRenderer.h
 *
 *  Created on: May 19, 2013
 *      Author: Tyler
 */

#ifndef CHUNKRENDERER_H_
#define CHUNKRENDERER_H_

#include "BaseRenderer.h"

class ChunkRenderer : public BaseRenderer{
public:
	ChunkRenderer();
	ChunkRenderer(int x, int y, int z, Block ** blockArray);
	virtual ~ChunkRenderer();

	void init(int x, int y, int z, Block ** blockArray);

	void setChunkPosition(int x, int y, int z);

	void render(Player * player);

	void addBlockAtPosition(int x, int y, int z);

protected:
	bool modelMatNeedsUpdate;

	glm::vec3 chunkPosition;
};

#endif /* CHUNKRENDERER_H_ */
