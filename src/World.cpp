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

}

World::~World() {
}

Chunk* World::getChunkAt(int x, int y, int z) {
	return chunkManager.getChunkWithCoordinate(x, y, z);
}

Block* World::getBlockAt(int x, int y, int z) {
	Chunk * chunk = chunkManager.getChunkWithCoordinate(x, y, z);
	x %= Chunk::CHUNK_SIZE;
	y %= Chunk::CHUNK_SIZE;
	z %= Chunk::CHUNK_SIZE;

	if(chunk != NULL){
		return chunk->getBlockAtCoordinate(x, y, z);
	} else {
		return NULL;
	}
}

void World::raytraceBlocks(glm::vec3 startPos, glm::vec3 endPos) {
	int startX = floorf((startPos.x < endPos.x ? startPos.x : endPos.x));
	int endX = ceilf((startPos.x > endPos.x ? startPos.x : endPos.x));
	int startY = floorf((startPos.y < endPos.y ? startPos.y : endPos.y));
	int endY = ceilf((startPos.y > endPos.y ? startPos.y : endPos.y));
	int startZ = floorf((startPos.z < endPos.z ? startPos.z : endPos.z));
	int endZ = ceilf((startPos.z > endPos.z ? startPos.z : endPos.z));

//	std::cout << startPos.x << ' ' << endPos.x << ' ' << startX << ' ' << endX << '\n';
//	std::cout << startPos.y << ' ' << endPos.y << ' ' << startY << ' ' << endY << '\n';
//	std::cout << startPos.z << ' ' << endPos.z << ' ' << startZ << ' ' << endZ << '\n';

	for(int x = startX; x < endX; ++x){
		for(int y = startY; y < endY; ++y){
			for (int z = startZ; z < endZ; ++z) {
				Chunk * currentChunk = chunkManager.getChunkWithCoordinate(x, y, z);
				Block * currentBlock = NULL;
				if (currentChunk) {
					currentBlock = currentChunk->getBlockAtCoordinate(x, y, z);
				}
				if(currentBlock && currentBlock->getBlockType() != blockType_Air){
					if(currentBlock->raytrace(x, y, z, startPos, endPos)){
						currentChunk->removeBlockAtPosition(x, y, z);
					}
//					std::cout << "raytrace " << x << "  " << y << ' ' << z << '\n';
				}
			}
		}
	}
}

} /* namespace ts */
