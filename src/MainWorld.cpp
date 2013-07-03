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
	entityList.push_back(mainPlayer);

	Entity * entity = new DynamicEntity(this, glm::vec3(0, 14, 0));
	entityList.push_back(entity);

	chunkManager = ChunkManager(mainPlayer);
}

MainWorld::~MainWorld() {
}

void MainWorld::handleInput() {
	//TODO move all input functions into update
}

void MainWorld::update(time_t dt) {
	for (std::vector<Entity *>::iterator iterator = entityList.begin(); iterator != entityList.end(); iterator++) {
		Entity *entity = *iterator;
		entity->update(dt);
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
