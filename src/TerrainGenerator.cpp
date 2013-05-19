/*
 * TerrainGenerator.cpp
 *
 *  Created on: May 16, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "TerrainGenerator.h"

#include <glm/gtx/noise.hpp>

#include <stdlib.h>//For rand()
#include <ctime>

namespace ts {

TerrainGenerator::TerrainGenerator() {
	srand(time(0));
	seed = rand();
}

TerrainGenerator::TerrainGenerator(int seed) {
	this->seed = seed;
}

TerrainGenerator::~TerrainGenerator() {
}

void TerrainGenerator::generateChunk(int genX, int genY, int genZ, BlockType * blockArray) {
	byte chunkSize = Chunk::CHUNK_SIZE;

	for (int x = 0; x < chunkSize; ++x) {
		for (int y = 0; y < chunkSize; ++y) {
			for (int z = 0; z < chunkSize; ++z) {
				int blockIndex = (x * chunkSize * chunkSize) + (y * chunkSize) + z;
				int height = (noiseGenerator.smoothNoise2D((x + genX) / (float) chunkSize, (z + genZ) / (float) chunkSize) + 1) * chunkSize / 2;
//				int height = (glm::noise1(glm::vec2((x + genX) / (float)chunkSize, (z + genZ) / (float)chunkSize)) + 1) * chunkSize / 2;
//				float density = glm::noise1(glm::vec3((x + genX) / (float)chunkSize, (y + genY) / (float) chunkSize, (z + genZ) / (float)chunkSize));
//				float density = noiseGenerator.smoothNoise3D((x + genX) / (float)chunkSize, (y + genY) / (float) chunkSize, (z + genZ) / (float)chunkSize);

				if (y + genY < height) {
//				if(y + genY < density * chunkSize){
					blockArray[blockIndex] = blockType_Grass;
				} else {
					blockArray[blockIndex] = blockType_Air;
				}
			}
		}
	}

	generateStructures(genX, genY, genZ, blockArray);
}

void TerrainGenerator::generateStructures(int genX, int genY, int genZ, BlockType * blockArray) {

}

} /* namespace ts */
