/*
 * ChunkManager.h
 *
 *  Created on: Mar 17, 2013
 *      Author: Tyler
 */

#ifndef CHUNKMANAGER_H_
#define CHUNKMANAGER_H_

#include "Common.h"
#include "Chunk.h"
#include "TerrainGenerator.h"

#include <glm/glm.hpp>

#include <vector>

class Player;

class ChunkManager {
public:
	ChunkManager();
	ChunkManager(Player * mainPlayer);
	virtual ~ChunkManager();

	void update(time_t dt);
	void draw(glm::mat4 *viewMat);

	void addChunk(int x, int y , int z, float r, float g, float b);
	void deleteChuck(int index);

	Chunk * getChunkWithCoordinate(int x, int y, int z);
private:
	std::vector<Chunk *> chunks;
	Player * mainPlayer;

	ts::TerrainGenerator generator;

	void loadChunks();
	void unloadChunks();
};

#endif /* CHUNKMANAGER_H_ */
