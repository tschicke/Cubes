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

	for (int x = genX; x < genX + chunkSize; ++x) {
		for (int z = genZ; z < genZ + chunkSize; ++z) {
			float height = (noiseGenerator.smoothNoise2D(x / (float) chunkSize, z / (float) chunkSize) + 1) * chunkSize / 2;
			for (int y = genY; y < genY + chunkSize; ++y) {
//				int height = (glm::noise1(glm::vec2((x + genX) / (float)chunkSize, (z + genZ) / (float)chunkSize)) + 1) * chunkSize / 2;
//				float density = glm::noise1(glm::vec3((x + genX) / (float)chunkSize, (y + genY) / (float) chunkSize, (z + genZ) / (float)chunkSize));
//				float density = noiseGenerator.smoothNoise3D((x + genX) / (float)chunkSize, (y + genY) / (float) chunkSize, (z + genZ) / (float)chunkSize);

				if (y == (int)height) {
//				if(y + genY < density * chunkSize){
					parentWorld->setBlockTypeAtPosition(x, y, z, blockType_Grass);
				} else if (y + genY < (int)height) {
					parentWorld->setBlockTypeAtPosition(x, y, z, blockType_Stone);
				} else if (parentWorld->getBlockAt(x, y, z) == NULL) {
					parentWorld->setBlockTypeAtPosition(x, y, z, blockType_Air);
				}
			}
			float test = ((x * z) % (int) height) / height;
			if(test < 0) test = -test;
			if(test > 0.5f && test < 0.52f){
				genTree(x, (int)height, z);
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

void TerrainGenerator::genTree(int startX, int startY, int startZ) {
	int centerX = startX, centerY = startY + 6, centerZ = startZ;
	for(int x = centerX - 2; x < centerX + 3; ++x){
		for(int y = centerY - 2; y < centerY + 3; ++y){
			for(int z = centerZ - 2; z < centerZ + 3; ++z){
				int radiusSquared = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) + (z - centerZ) * (z - centerZ);
				if(radiusSquared <= 4){
					parentWorld->setBlockTypeAtPosition(x, y, z, blockType_Dirt);
				}
			}
		}
	}

	for(int y = startY; y < startY + 6; ++y){
		parentWorld->setBlockTypeAtPosition(centerX, y, centerZ, blockType_Tree);
	}
}

} /* namespace ts */
