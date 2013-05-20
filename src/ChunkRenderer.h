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
	ChunkRenderer(int x, int y, int z);
	virtual ~ChunkRenderer();

	void setChunkPosition(int x, int y, int z);

	void render(Player * player);

protected:
};

#endif /* CHUNKRENDERER_H_ */
