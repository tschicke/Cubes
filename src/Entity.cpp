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
	model.deleteBuffers();
}

void Entity::init(ts::World* world, glm::vec3 position) {
	parentWorld = world;

	this->position = position;

	yaw = 0;
	pitch = 0;

	model.init(getModelPath(), this);
}

void Entity::draw() {
	if(parentWorld != NULL){
		model.render();
	}
}

CollisionBox Entity::getCollisionBox() {
	return CollisionBox(position, halfDimentions);
}

void Entity::update(time_t dt) {
	model.update();
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

int Entity::getYaw() {
	return yaw;
}

int Entity::getPitch() {
	return pitch;
}

void Entity::setYaw(int yaw) {
	if (this->yaw != yaw) {
		model.markNeedsMatrixUpdate();
		this->yaw = yaw;
		yaw %= 360;
	}
}

void Entity::setPitch(int pitch) {
	if (this->pitch != pitch) {
		model.markNeedsMatrixUpdate();
		this->pitch = pitch;
		pitch %= 360;
	}
}

void Entity::incrementYaw(int delta) {
	if (delta != 0) {
		model.markNeedsMatrixUpdate();
		yaw += delta;
		yaw %= 360;
	}
}

const char* Entity::getModelPath() {
	return "models/Sword.model";//TODO should be a default/NULL model
}

void Entity::setPosition(glm::vec3 position) {
	this->position = position;
}

void Entity::incrementPitch(int delta) {
	if (delta != 0) {
		model.markNeedsMatrixUpdate();
		pitch += delta;
		pitch %= 360;
	}

}
