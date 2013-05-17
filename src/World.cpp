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

} /* namespace ts */
