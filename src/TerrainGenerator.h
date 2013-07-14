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
class World;
}

namespace ts {

class TerrainGenerator {
public:
	TerrainGenerator();
	TerrainGenerator(World * parentWorld);
	virtual ~TerrainGenerator();

	void generateChunk(int x, int y, int z);

	void setSeed(int seed);

	void setParentWorld(World * parentWorld);
private:
	void genTree(int x, int y, int z);

	int seed;

	World * parentWorld;

	Noise noiseGenerator;
};

} /* namespace ts */
#endif /* TERRAINGENERATOR_H_ */
