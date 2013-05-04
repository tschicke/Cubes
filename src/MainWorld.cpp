/*
 * MainWorld.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Tyler
 */

#include "MainWorld.h"
#include <iostream>

namespace ts {

MainWorld::MainWorld() {
	mainPlayer = new Player(this);
	mainPlayer->setPosition(glm::vec3(0, 32, 0));
	characters.push_back(mainPlayer);

	chunkManager = ChunkManager(mainPlayer);

//	for (int x = (mainPlayer->getPosition().x / Chunk::CHUNK_SIZE - 4); x < (mainPlayer->getPosition().x / Chunk::CHUNK_SIZE) + 4; ++x){//TODO should be in chunkmanager class not world class
//		int y = (mainPlayer->getPosition().y / Chunk::CHUNK_SIZE) - 1;//TODO make this a for loop
//		for(int z = (mainPlayer->getPosition().z / Chunk::CHUNK_SIZE - 4); z < (mainPlayer->getPosition().z / Chunk::CHUNK_SIZE) + 4; ++z){
//			chunkManager.addChunk(x * Chunk::CHUNK_SIZE, y * Chunk::CHUNK_SIZE, z * Chunk::CHUNK_SIZE, 1, 1, 1);
//		}
//	}
}

MainWorld::~MainWorld() {
}

void MainWorld::handleInput() {
	//TODO move all input functions into update
}

void MainWorld::update(time_t dt) {
	for (std::vector<Character *>::iterator iterator = characters.begin(); iterator != characters.end(); iterator++) {
		Character *character = *iterator;
		character->update(dt);
	}
	chunkManager.update(dt);
}

void MainWorld::draw() {
	for (std::vector<Character *>::iterator iterator = characters.begin(); iterator != characters.end(); iterator++) {
		Character *character = *iterator;
		character->draw(mainPlayer->getCameraViewMatrix());
	}
	chunkManager.draw(mainPlayer->getCameraViewMatrix());
}

} /* namespace ts */
