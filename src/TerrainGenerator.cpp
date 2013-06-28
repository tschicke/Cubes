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

				if (y + genY == height) {
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

	generateStructures(genX, genY, genZ, blockTypes);

	for (int i = 0; i < chunkSize * chunkSize * chunkSize; ++i) {
		delete blockArray[i];
		blockArray[i] = Block::getBlockOfType(blockTypes[i]);
	}
}

void TerrainGenerator::generateStructures(int genX, int genY, int genZ, BlockType * blockArray) {
	for (int x = 3; x < 12; ++x) {
		for (int z = 0; z < 8; ++z) {
			for (int y = 10; y < 20; ++y) {
				int chunkSize = Chunk::CHUNK_SIZE;
				int blockIndex = (x * 1) * chunkSize * chunkSize + y * chunkSize + (z * 1);

				if (x == 3 || x == 11 || z == 0 || z == 7 || y == 10 || y == 19) { //House Outline
					blockArray[blockIndex] = blockType_Tree;
				} else {
					blockArray[blockIndex] = blockType_Air;
				}

				if ((x == 6 || x == 7 || x == 8) && z == 0 && (y == 11 || y == 12)) { //Door
					blockArray[blockIndex] = blockType_Air;
				}


				if(y == 19 && (x > 7 && x < 11) && z == 6){
					blockArray[blockIndex] = blockType_Air;
				}

				if(z == 6 && (x > 3 && x < 11)){
					int height = x + 7;
					if(y == height){
						blockArray[blockIndex] = blockType_Tree;
					}
				}
			}
		}
	}

	for (int x = 2; x < 13; ++x) {
		int height = -abs(x - 7) + 25;
		for (int y = 20; y < 30; ++y) {
			for (int z = 0; z < 8; ++z) {
				int chunkSize = Chunk::CHUNK_SIZE;
				int blockIndex = x * chunkSize * chunkSize + y * chunkSize + z;

				if(y == height || (y < height && (z == 0 || z == 7))){
					blockArray[blockIndex] = blockType_Tree;
				}

				if(y > 20 && y < 23 && z == 0 && x > 5 && x < 9){
					blockArray[blockIndex] = blockType_Air;
				}
			}
		}
	}
}

} /* namespace ts */
