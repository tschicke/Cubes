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
#include "BlockStorage.h"
#include "ChunkRenderer.h"

class Player;//should be include?

class Chunk{
public:
	Chunk();
	virtual ~Chunk();

	void init(int x, int y, int z);

	void update(time_t dt);
	void draw(Player * player);

	glm::vec3 getChunkPos();

	static const int CHUNK_SIZE = 32;

	Block * getBlockAtCoordinate(int x, int y, int z);

	bool isLoaded();

	void setTestColor(float r, float b, float g);

	//New Public Stuff
	friend class BlockStorage;//Need this?
private:
	Block ** blocks;

	MeshID meshID;
	ShaderProgram shaderProgram;

	void createCube(int x, int y, int z);//Temp??
	int indexOfBlockAt(int x, int y, int z);//Change to return int?

	glm::vec3 chunkPosition;//Should be glm::vec3?
	glm::vec3 testColor;

	bool loaded;

	//New Private Stuff
	ChunkRenderer chunkRenderer;
	BlockStorage * blockStorage;

};

#endif /* CHUNK_H_ */
