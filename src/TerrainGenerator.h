/*
 * TerrainGenerator.h
 *
 *  Created on: May 16, 2013
 *      Author: Tyler
 */

#ifndef TERRAINGENERATOR_H_
#define TERRAINGENERATOR_H_

#include "Chunk.h"

namespace ts {

class TerrainGenerator {
public:
	TerrainGenerator();
	virtual ~TerrainGenerator();

	void generateChunk(int x, int z, BlockType * blockTypeArray);
};

} /* namespace ts */
#endif /* TERRAINGENERATOR_H_ */
