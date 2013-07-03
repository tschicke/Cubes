/*
 * DynamicEntity.cpp
 *
 *  Created on: Jun 30, 2013
 *      Author: Tyler
 */

#include "DynamicEntity.h"

#include <iostream>

DynamicEntity::DynamicEntity() {
}

DynamicEntity::DynamicEntity(ts::World* world, glm::vec3 position) {
	init(world, position, glm::vec3());
}

DynamicEntity::DynamicEntity(ts::World * world, glm::vec3 position, glm::vec3 velocity) {
	init(world, position, velocity);
}

DynamicEntity::~DynamicEntity() {
}

void DynamicEntity::move(glm::vec3 moveVec) {
	position += moveVec;
	renderer.markNeedsMatrixUpdate();
}

void DynamicEntity::addYaw(float yaw) {
	this->yaw += yaw;
}

void DynamicEntity::update(time_t dt) {
	move(velocity * (dt / 1000.f));
}

void DynamicEntity::init(ts::World* world, glm::vec3 position, glm::vec3 velocity) {
	Entity::init(world, position);
	this->velocity = velocity;
}

void DynamicEntity::addPitch(float pitch) {
	this->pitch += pitch;
}

