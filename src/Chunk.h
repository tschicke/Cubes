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
#include "BlockStorage.h"
#include "ChunkRenderer.h"

class Player;
//should be include?

class Chunk {
public:
	enum State/* : char*/ {
		initialize, rebuild, unload, render
	};

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

	void setBlockTypeAtPosition(int x, int y, int z, BlockType type);

	State getChunkState();

	friend class BlockStorage; //Need this?
	friend class ChunkRenderer;
private:
	int indexOfBlockAt(int x, int y, int z);

	glm::vec3 chunkPosition;
	glm::vec3 testColor;

	bool loaded;

	ChunkRenderer chunkRenderer;
	BlockStorage * blockStorage;

	State chunkState;
};

#endif /* CHUNK_H_ */
