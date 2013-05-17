/*
 * TerrainGenerator.cpp
 *
 *  Created on: May 16, 2013
 *      Author: Tyler
 */

#include "TerrainGenerator.h"

namespace ts {

TerrainGenerator::TerrainGenerator() {

}

TerrainGenerator::~TerrainGenerator() {
}

void TerrainGenerator::generateChunk(int x, int z, BlockType * blockArray){
	byte chunkSize = Chunk::CHUNK_SIZE;

	for(int x = 0; x < chunkSize; ++x){
		for(int y = 0; x < chunkSize; ++x){
			for(int z = 0; x < chunkSize; ++x){
				blockArray[(x * chunkSize * chunkSize) + (y * chunkSize) + z] = blockType_Dirt;
			}
		}
	}
}

} /* namespace ts */
