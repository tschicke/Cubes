/*
 * ChunkRenderer.h
 *
 *  Created on: May 19, 2013
 *      Author: Tyler
 */

#ifndef CHUNKRENDERER_H_
#define CHUNKRENDERER_H_

#include "BlockTypes.h"
#include "BaseRenderer.h"

#include "Common.h"

class Chunk;

class ChunkRenderer : public BaseRenderer{
public:
	ChunkRenderer();
	ChunkRenderer(int x, int y, int z, Chunk * parentChunk);
	virtual ~ChunkRenderer();

	void init(int x, int y, int z, Chunk * parentChunk);

	void setChunkPosition(int x, int y, int z);

	void update(time_t dt);
	void render(Player * player);

	void updateBlockAtPosition(int x, int y, int z);
	void markIndicesDirty();

protected:
	bool modelMatNeedsUpdate;

	Chunk * parentChunk;

	glm::vec3 chunkPosition;

	int numVerticesToDraw;

	void remakeIndexBuffer();
	bool needsIndexBufferRemake;
};

#endif /* CHUNKRENDERER_H_ */
