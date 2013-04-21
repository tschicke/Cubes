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

} /* namespace ts */
