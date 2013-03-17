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
#include <glm/glm.hpp>

#include "BlockTypes.h"
#include "Renderer.h"
#include "Shader.h"

class Chunk{
public:
	Chunk();
	Chunk(int x, int y, int z);
	virtual ~Chunk();

	void init(int x, int y, int z);

	void update(time_t dt);
	void draw(glm::mat4* viewMatrix);

	static const int CHUNK_SIZE = 32;
private:
	Block ** blocks;

	MeshID meshID;
	ShaderProgram shaderProgram;

	void createCube(int x, int y, int z);//Temp??
	Block ** blockAt(int x, int y, int z);//Change to return int?

	int x, y, z;//Should be glm::vec3?
};

#endif /* CHUNK_H_ */
