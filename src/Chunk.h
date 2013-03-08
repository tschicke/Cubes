/*
 * Chunk.h
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */

#ifndef CHUNK_H_
#define CHUNK_H_

#include "Common.h"

#include <vector>

#include "BlockTypes.h"
#include "Renderer.h"
#include "Shader.h"

class Chunk{
	//TODO make super typedef??
public:
	Chunk();
	Chunk(int x, int y, int z);
	virtual ~Chunk();

	void init(int x, int y, int z);

	void update(time_t dt);
	void draw(Renderer * renderer);

	static const int CHUNK_SIZE = 16;
private:
	Block ** blocks;

	MeshID meshID;
	ShaderProgram shaderProgram;

	void createCube(int x, int y, int z);//Temp??
	Block ** blockAt(int x, int y, int z);//Change to return int?
};

#endif /* CHUNK_H_ */
