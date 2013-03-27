/*
 * World.cpp
 *
 *  Created on: Mar 26, 2013
 *      Author: Tyler
 */

#include "World.h"

namespace ts {

World::World() {

}

World::~World() {
}

void World::update(time_t dt){
	chunkManager.update(dt);
	characters[0].update(dt);
}

void World::pushCharacter(Player newPlayer) {
	characters.push_back(newPlayer);
}

} /* namespace ts */
