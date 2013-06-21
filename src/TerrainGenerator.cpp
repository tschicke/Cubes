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

void TerrainGenerator::generateChunk(int genX, int genY, int genZ, Block ** blockArray) {
	byte chunkSize = Chunk::CHUNK_SIZE;

	BlockType * blockTypes = new BlockType[chunkSize * chunkSize * chunkSize];

	for (int x = 0; x < chunkSize; ++x) {
		for (int z = 0; z < chunkSize; ++z) {
			int height = (noiseGenerator.smoothNoise2D((x + genX) / (float) chunkSize, (z + genZ) / (float) chunkSize) + 1) * chunkSize / 2;
			for (int y = 0; y < chunkSize; ++y) {
				int blockIndex = (x * chunkSize * chunkSize) + (y * chunkSize) + z;
//				int height = (glm::noise1(glm::vec2((x + genX) / (float)chunkSize, (z + genZ) / (float)chunkSize)) + 1) * chunkSize / 2;
//				float density = glm::noise1(glm::vec3((x + genX) / (float)chunkSize, (y + genY) / (float) chunkSize, (z + genZ) / (float)chunkSize));
//				float density = noiseGenerator.smoothNoise3D((x + genX) / (float)chunkSize, (y + genY) / (float) chunkSize, (z + genZ) / (float)chunkSize);

				if (y + genY == height) { //TODO change to blocktype array to avoid allocations that get changed in generatestructures??
//				if(y + genY < density * chunkSize){
					blockTypes[blockIndex] = blockType_Grass;
				} else if (y + genY < height) {
					blockTypes[blockIndex] = blockType_Stone;
				} else {
					blockTypes[blockIndex] = blockType_Air;
				}
			}
		}
	}

	for(int i = 0; i < chunkSize * chunkSize * chunkSize; ++i){
		blockArray[i] = Block::getBlockOfType(blockTypes[i]);
	}

	generateStructures(genX, genY, genZ, blockArray);
}

void TerrainGenerator::generateStructures(int genX, int genY, int genZ, Block ** blockArray) {

}

} /* namespace ts */
