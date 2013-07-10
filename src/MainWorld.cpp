/*
 * MainWorld.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Tyler
 */

#include "MainWorld.h"
#include <iostream>

#include "DynamicEntity.h"

namespace ts {

MainWorld::MainWorld() {
	mainPlayer = new Player(this);
	mainPlayer->setPosition(glm::vec3(0, 32, 0));
	addEntity(mainPlayer);
	addEntity(new DynamicEntity(this, glm::vec3(1, 32, 1), glm::vec3()));
	addEntity(new DynamicEntity(this, glm::vec3(2, 32, 1), glm::vec3()));

	chunkManager = ChunkManager(mainPlayer);
}

MainWorld::~MainWorld() {
}

void MainWorld::handleInput() {
	//TODO move all input functions into update
}

void MainWorld::update(time_t dt) {
	for(unsigned int i = 0; i < entityList.size(); ++i) {
		Entity *entity = entityList[i];
		entity->update(dt);
		if(entity->shouldBeDeleted()){
			delete entity;
			entityList.erase(entityList.begin() + i);
		}
	}

	chunkManager.update(dt);
}

void MainWorld::draw() {
	for (std::vector<Entity *>::iterator iterator = entityList.begin(); iterator != entityList.end(); iterator++) {
		Entity *entity = *iterator;
		entity->draw();
	}

	chunkManager.draw(mainPlayer->getCameraViewMatrix());
}

} /* namespace ts */
