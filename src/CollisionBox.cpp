/*
 * CollisionBox.cpp
 *
 *  Created on: Jul 3, 2013
 *      Author: Tyler
 */

#include "CollisionBox.h"

CollisionBox::CollisionBox() {

}

CollisionBox::CollisionBox(glm::vec3 position, glm::vec3 halfDimentions) {
	this->position = position;
	this->halfDimentions = halfDimentions;
}

CollisionBox::~CollisionBox() {
}

