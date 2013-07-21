/*
 * World.h
 *
 *  Created on: Mar 26, 2013
 *      Author: Tyler
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "Common.h"
#include "ChunkManager.h"
#include "Player.h"
#include "Character.h"

#include "TerrainGenerator.h"

#include "SelectedBlock.h"

namespace ts {

class World {
public:
	World();
	virtual ~World();

	virtual void handleInput() = 0;
	virtual void update(time_t dt) = 0;
	virtual void draw() = 0;

	Chunk * getChunkAt(int x, int y, int z);
	Block * getBlockAt(int x, int y, int z);

	void raytraceBlocks(glm::vec3 startPos, glm::vec3 endPos, SelectedBlock * selectedBlock);

	void setBlockTypeAtPosition(int x, int y, int z, BlockType type);

	Player * getMainPlayer();

	void addEntity(Entity * entity);
	void clearEntities();

	TerrainGenerator * getWorldGenerator();
protected:
	ChunkManager chunkManager;

	Player * mainPlayer;
	std::vector<Entity *> entityList;

	TerrainGenerator * generator;
};

} /* namespace ts */
#endif /* WORLD_H_ */
