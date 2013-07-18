/*
 * Entity.cpp
 *
 *  Created on: Jun 29, 2013
 *      Author: Tyler
 */

#include "Entity.h"

#include "World.h"

#include <iostream>

Entity::Entity() {
	parentWorld = NULL;

	flagShouldBeDeleted = false;

	yaw = 0;
	pitch = 0;
}

Entity::Entity(ts::World* world, glm::vec3 position) {
	init(world, position);
}

Entity::~Entity() {
	renderer.deleteBuffers();
}

void Entity::init(ts::World* world, glm::vec3 position) {
	parentWorld = world;

	this->position = position;

	yaw = 0;
	pitch = 0;

	renderer = EntityRenderer(this, NULL);
}

void Entity::draw() {
	if(parentWorld != NULL){
		renderer.render();
	}
}

CollisionBox Entity::getCollisionBox() {
	return CollisionBox(position, halfDimentions);
}

void Entity::update(time_t dt) {
}

bool Entity::shouldBeDeleted() {
	return flagShouldBeDeleted;
}

glm::vec3 Entity::getPosition() {
	return position;
}

void Entity::deleteEntity() {
	flagShouldBeDeleted = true;
}
