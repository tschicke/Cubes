/*
 * ChunkRenderer.h
 *
 *  Created on: May 18, 2013
 *      Author: Tyler
 */

#ifndef CHUNKRENDERER_H_
#define CHUNKRENDERER_H_

#include "Common.h"

class BaseRenderer {
public:
	BaseRenderer();
	virtual ~BaseRenderer();

	unsigned int createBufferWithSize(int size, bool vertexBuffer);
	void deleteBuffer(uint& buffer);

	void substituteDataToVertexBuffer(uint bufferID, int size, int offset, float * data);
	void substituteDataToVertexBuffer(uint bufferID, int size, int offset, int * data);

	void substituteDataToIndexBuffer(uint bufferID, int size, int offset, int * data);

	void bindVertexBuffer(uint buffer); //should be bindArrayBuffer?
	void bindIndexBuffer(uint buffer); //should be bindIndexArrayBuffer?

	void unbindVertexBuffer(); //should be bindArrayBuffer?
	void unbindIndexBuffer(); //should be bindIndexArrayBuffer?

	void render();
};

#endif /* CHUNKRENDERER_H_ */
