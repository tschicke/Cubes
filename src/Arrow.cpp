/*
 * Arrow.cpp
 *
 *  Created on: Jul 30, 2013
 *      Author: Tyler
 */

#include "Arrow.h"
#include <iostream>

Arrow::Arrow() {

}

Arrow::Arrow(ts::World* parentWorld, glm::vec3 position, glm::vec3 velocity)
{
	init(parentWorld, position, velocity);
}

Arrow::~Arrow() {
}

void Arrow::update(time_t dt) {
	DynamicEntity::update(dt);
	if(!(floorColl || ceilColl || xColl || zColl)){
		incrementPitch(-2);
	}
}

const char* Arrow::getModelPath() {
	return "models/Arrow.model";
}
