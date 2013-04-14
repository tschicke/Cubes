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

	//Temp
	chunkManager.addChunk(0, 0, 0, 1, 1, 1);
	chunkManager.addChunk(Chunk::CHUNK_SIZE, 0, 0, 1, 0, 0);
	chunkManager.addChunk(Chunk::CHUNK_SIZE, 0, Chunk::CHUNK_SIZE, 0, 1, 0);
	chunkManager.addChunk(0, 0, Chunk::CHUNK_SIZE, 0, 0, 1);
}

MainWorld::~MainWorld() {
}

void MainWorld::handleInput() {
	//TODO move all input functions into update
}

void MainWorld::update(time_t dt) {
	for (std::vector<Character *>::iterator iterator = characters.begin(); iterator != characters.end(); iterator++) { //TODO add max limit per frame
		Character *character = *iterator;
		character->update(dt);
	}
	chunkManager.update(dt);
}

void MainWorld::draw() {
	for (std::vector<Character *>::iterator iterator = characters.begin(); iterator != characters.end(); iterator++) { //TODO add max limit per frame
		Character *character = *iterator;
		character->draw(mainPlayer->getCameraViewMatrix());
	}
	chunkManager.draw(mainPlayer->getCameraViewMatrix());
}

} /* namespace ts */
