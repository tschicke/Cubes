/*
 * World.cpp
 *
 *  Created on: Mar 26, 2013
 *      Author: Tyler
 */

#include "World.h"

#include <iostream>

namespace ts {

World::World() {
	mainPlayer = NULL;

	generator = NULL;
}

World::~World() {
	for(std::vector<Entity *>::iterator iterator = entityList.begin(); iterator != entityList.end(); ++iterator){
		delete *iterator;
	}
}

Chunk* World::getChunkAt(int x, int y, int z) {
	return chunkManager.getChunkWithCoordinate(x, y, z);
}

Block* World::getBlockAt(int x, int y, int z) {
	Chunk * chunk = chunkManager.getChunkWithCoordinate(x, y, z);
	x %= Chunk::CHUNK_SIZE;
	y %= Chunk::CHUNK_SIZE;
	z %= Chunk::CHUNK_SIZE;

	if (chunk != NULL) {
		return chunk->getBlockAtCoordinate(x, y, z);
	} else {
		return NULL;
	}
}

void World::raytraceBlocks(glm::vec3 startPos, glm::vec3 endPos, SelectedBlock * selectedBlock) {
	bool posXChange = endPos.x > startPos.x;
	bool posYChange = endPos.y > startPos.y;
	bool posZChange = endPos.z > startPos.z;

	int startX = (posXChange ? floorf(startPos.x) : ceilf(startPos.x));
	int endX = (posXChange ? ceilf(endPos.x) : floorf(endPos.x));
	int startY = (posYChange ? floorf(startPos.y) : ceilf(startPos.y));
	int endY = (posYChange ? ceilf(endPos.y) : floorf(endPos.y));
	int startZ = (posZChange ? floorf(startPos.z) : ceilf(startPos.z));
	int endZ = (posZChange ? ceilf(endPos.z) : floorf(endPos.z));

	int xChange = (posXChange ? 1 : -1);
	int yChange = (posYChange ? 1 : -1);
	int zChange = (posZChange ? 1 : -1);

	for (int x = startX; x != endX + xChange; x += xChange) {
		for (int y = startY; y != endY + yChange; y += yChange) {
			for (int z = startZ; z != endZ + zChange; z += zChange) {
				Chunk * currentChunk = chunkManager.getChunkWithCoordinate(x, y, z);
				Block * currentBlock = NULL;
				if (currentChunk) {
					currentBlock = currentChunk->getBlockAtCoordinate(x, y, z);
				}
				if (currentBlock && currentBlock->getBlockType() != blockType_Air) {
					Face face = currentBlock->raytrace(x, y, z, startPos, endPos);
					if (face != face_nocollision) {
						selectedBlock->set(x, y, z, currentBlock, face);
						return;
					}
				}
			}
		}
	}

	selectedBlock->set(0, 0, 0, NULL, face_nocollision);
}

void World::setBlockTypeAtPosition(int x, int y, int z, BlockType type){
	Chunk * chunk = chunkManager.getChunkWithCoordinate(x, y, z);

//	if(chunk == NULL){
//		chunkManager.addChunk(x, y, z, 1, 1, 1);
//	}
//
//	chunk = chunkManager.getChunkWithCoordinate(x, y, z);

	if(chunk != NULL){
		chunk->setBlockTypeAtPosition(x, y, z, type);
	}
}

Player* World::getMainPlayer() {
	return mainPlayer;
}

void World::addEntity(Entity* entity) {
	if(entity != NULL){
		entityList.push_back(entity);
	}
}

void World::clearEntities() {
	std::vector<Entity *>::iterator iterator;
	for(iterator = entityList.begin(); iterator != entityList.end(); ++iterator){
		Entity * entity = *iterator;
		if(entity != mainPlayer) entity->deleteEntity();
	}
}

TerrainGenerator* World::getWorldGenerator() {
	return generator;
}

} /* namespace ts */
