/*
 * TerrainGenerator.cpp
 *
 *  Created on: May 16, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "TerrainGenerator.h"

#include "World.h"

#include <glm/gtx/noise.hpp>

#include <stdlib.h>//For rand()
#include <ctime>

namespace ts {

TerrainGenerator::TerrainGenerator() {
	srand(time(0));
	seed = rand();

	parentWorld = NULL;
}

TerrainGenerator::TerrainGenerator(World * parentWorld) {
	srand(time(0));
	seed = rand();

	this->parentWorld = parentWorld;
}

TerrainGenerator::~TerrainGenerator() {
}

void TerrainGenerator::generateChunk(int genX, int genY, int genZ) {
	byte chunkSize = Chunk::CHUNK_SIZE;

	for (int x = 0; x < chunkSize; ++x) {
		for (int z = 0; z < chunkSize; ++z) {
			int height = (noiseGenerator.smoothNoise2D((x + genX) / (float) chunkSize, (z + genZ) / (float) chunkSize) + 1) * chunkSize / 2;
			for (int y = 0; y < chunkSize; ++y) {
//				int height = (glm::noise1(glm::vec2((x + genX) / (float)chunkSize, (z + genZ) / (float)chunkSize)) + 1) * chunkSize / 2;
//				float density = glm::noise1(glm::vec3((x + genX) / (float)chunkSize, (y + genY) / (float) chunkSize, (z + genZ) / (float)chunkSize));
//				float density = noiseGenerator.smoothNoise3D((x + genX) / (float)chunkSize, (y + genY) / (float) chunkSize, (z + genZ) / (float)chunkSize);

				int chunkX = x + genX, chunkY = y + genY, chunkZ = z + genZ;

				if (y + genY == height) {
//				if(y + genY < density * chunkSize){
					parentWorld->setBlockTypeAtPosition(chunkX, chunkY, chunkZ, blockType_Air);
				} else if (y + genY < height) {
					parentWorld->setBlockTypeAtPosition(chunkX, chunkY, chunkZ, blockType_Stone);
				} else {
					parentWorld->setBlockTypeAtPosition(chunkX, chunkY, chunkZ, blockType_Air);
				}
			}
		}
	}
}

//void TerrainGenerator::generateStructures(int genX, int genY, int genZ, BlockType * blockArray) {
//	for (int x = 3; x < 12; ++x) {
//		for (int z = 0; z < 8; ++z) {
//			for (int y = 10; y < 20; ++y) {
//				int chunkSize = Chunk::CHUNK_SIZE;
//				int blockIndex = (x * 1) * chunkSize * chunkSize + y * chunkSize + (z * 1);
//
//				if (x == 3 || x == 11 || z == 0 || z == 7 || y == 10 || y == 19) { //House Outline
//					blockArray[blockIndex] = blockType_Tree;
//				} else {
//					blockArray[blockIndex] = blockType_Air;
//				}
//
//				if ((x == 6 || x == 7 || x == 8) && z == 0 && (y == 11 || y == 12)) { //Door
//					blockArray[blockIndex] = blockType_Air;
//				}
//
//
//				if(y == 19 && (x > 7 && x < 11) && z == 6){
//					blockArray[blockIndex] = blockType_Air;
//				}
//
//				if(z == 6 && (x > 3 && x < 11)){
//					int height = x + 7;
//					if(y == height){
//						blockArray[blockIndex] = blockType_Tree;
//					}
//				}
//			}
//		}
//	}
//
//	for (int x = 2; x < 13; ++x) {
//		int height = -abs(x - 7) + 25;
//		for (int y = 20; y < 30; ++y) {
//			for (int z = 0; z < 8; ++z) {
//				int chunkSize = Chunk::CHUNK_SIZE;
//				int blockIndex = x * chunkSize * chunkSize + y * chunkSize + z;
//
//				if(y == height || (y < height && (z == 0 || z == 7))){
//					blockArray[blockIndex] = blockType_Tree;
//				}
//
//				if(y > 20 && y < 23 && z == 0 && x > 5 && x < 9){
//					blockArray[blockIndex] = blockType_Air;
//				}
//			}
//		}
//	}
//}

void TerrainGenerator::setSeed(int seed) {
	this->seed = seed;
}

void TerrainGenerator::setParentWorld(World* parentWorld) {
	this->parentWorld = parentWorld;
}

} /* namespace ts */
