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

	yaw = 0;
	pitch = 0;
	std::cout << "default entity\n";
}

Entity::Entity(ts::World* world, float x, float y, float z) {
	init(world, glm::vec3(x, y, z));
}

Entity::Entity(ts::World* world, glm::vec3 position) {
	init(world, position);
}

Entity::~Entity() {
	std::cout << "entity deconst\n";
}

void Entity::init(ts::World* world, glm::vec3 position) {
	parentWorld = world;

	this->position = position;

	yaw = 0;
	pitch = 0;

	std::cout << position.x << ' ' << position.y << ' ' << position.z << '\n';

	std::cout << "e const " << this << '\n';
	renderer = EntityRenderer(this, NULL);
}

void Entity::draw() {
	if(parentWorld != NULL){
		renderer.render(parentWorld->getMainPlayer());
		std::cout << "entity " << this << '\n';
	}
}

void Entity::move(float x, float y, float z) {
	move(glm::vec3(x, y, z));
}

void Entity::move(glm::vec3 moveVec) {
	position += moveVec;
	renderer.markNeedsMatrixUpdate();
}

void Entity::addYaw(float yaw) {
	this->yaw += yaw;
}

void Entity::addPitch(float pitch) {
	this->pitch += pitch;
}
