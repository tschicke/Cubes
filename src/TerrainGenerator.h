/*
 * TerrainGenerator.h
 *
 *  Created on: May 16, 2013
 *      Author: Tyler
 */

#ifndef TERRAINGENERATOR_H_
#define TERRAINGENERATOR_H_

#include "Chunk.h"

#include "Noise.h"//Temp

namespace ts {

class TerrainGenerator {
public:
	TerrainGenerator();
	TerrainGenerator(int seed);
	virtual ~TerrainGenerator();

	void generateChunk(int x, int y, int z, BlockType * blockTypeArray);
private:
	int seed;

	Noise noiseGenerator;
};

} /* namespace ts */
#endif /* TERRAINGENERATOR_H_ */
