/*
 * DynamicEntity.cpp
 *
 *  Created on: Jun 30, 2013
 *      Author: Tyler
 */

#include "DynamicEntity.h"

#include "World.h"

#include <iostream>

DynamicEntity::DynamicEntity() {
	affectedByGravity = false;
	xColl = zColl = floorColl = ceilColl = false;
}

DynamicEntity::DynamicEntity(ts::World* world, glm::vec3 position) {
	init(world, position, glm::vec3());
}

DynamicEntity::DynamicEntity(ts::World * world, glm::vec3 position, glm::vec3 velocity) {
	init(world, position, velocity);
}

void DynamicEntity::init(ts::World* world, glm::vec3 position, glm::vec3 velocity) {
	Entity::init(world, position);
	affectedByGravity = true;
	this->velocity = velocity;
	xColl = zColl = floorColl = ceilColl = false;
}

DynamicEntity::~DynamicEntity() {
}

void DynamicEntity::move(glm::vec3 moveVec) {
	if (moveVec.x != 0 || moveVec.y != 0 || moveVec.z != 0) {
		position += moveVec;
		model.markNeedsMatrixUpdate();
	}
}

void DynamicEntity::update(time_t dt) {
	Entity::update(dt);
	if (affectedByGravity) {
		velocity.y -= 0.005f;
	}
	checkCollisions();

	move(velocity + moveVector);
	if (floorColl) {
//		flagShouldBeDeleted = true;
		velocity = glm::vec3();
	} else if (ceilColl || xColl || zColl) {
//		flagShouldBeDeleted = true;
		velocity = glm::vec3();
		affectedByGravity = false;
	}

	moveVector = glm::vec3();
}

void DynamicEntity::checkCollisions() {
	glm::vec3 nextPosition = position + moveVector + velocity;

	CollisionBox box = getCollisionBox();

	//X checks
	if (nextPosition.x != position.x) {
		for (int c = 0; c < 12; ++c) {
			float xt = (nextPosition.x + (c % 2 * (box.halfDimentions.x * 2)) - box.halfDimentions.x);
			float yt = (position.y + (c / 4 * box.halfDimentions.y));
			float zt = (position.z + ((c % 4) / 2 * (box.halfDimentions.z * 2)) - box.halfDimentions.z);	// - (c / 2 * -0.01) is temp

			Block * nextBlockX = parentWorld->getBlockAt(floorf(xt), floorf(yt), floorf(zt));
			if (nextBlockX != NULL && nextBlockX->isSolid()) {
				moveVector.x = roundf(xt) - (position.x + (c % 2 * ((box.halfDimentions.x * 2) + 0.001f)) - (box.halfDimentions.x + 0.0005f));
				velocity.x = 0;

				xColl = true;
				break;
			} else {
				xColl = false;
			}
		}
	}

	nextPosition = position + moveVector + velocity;

	//Z checks
	if (nextPosition.z != position.z) {
		for (int c = 0; c < 12; ++c) {
			float zt = (nextPosition.z + (c % 2 * (box.halfDimentions.z * 2)) - box.halfDimentions.z);
			float yt = (position.y + (c / 4 * box.halfDimentions.y));
			float xt = (nextPosition.x + ((c % 4) / 2 * (box.halfDimentions.x * 2)) - box.halfDimentions.x);	// - (c / 2 * -0.01) is temp

			Block * nextBlockZ = parentWorld->getBlockAt(floorf(xt), floorf(yt), floorf(zt));
			if (nextBlockZ != NULL && nextBlockZ->isSolid()) {
				moveVector.z = roundf(zt) - (position.z + (c % 2 * ((box.halfDimentions.z * 2) + 0.001f)) - (box.halfDimentions.z + 0.0005f));
				velocity.z = 0;

				zColl = true;
				break;
			} else {
				zColl = false;
			}
		}
	}

	nextPosition = position + moveVector + velocity;

	//Y checks
	if (nextPosition.y != position.y) {
		for (int c = 0; c < 8; ++c) {
			float zt = (nextPosition.z + (c % 2 * (box.halfDimentions.z * 2)) - box.halfDimentions.z);
			float yt = (nextPosition.y + (c / 4 * (box.halfDimentions.y * 2)));
			float xt = (nextPosition.x + ((c % 4) / 2 * (box.halfDimentions.x * 2)) - box.halfDimentions.x);	// - (c / 2 * -0.01) is temp

			Block * nextBlockY = parentWorld->getBlockAt(floorf(xt), floorf(yt), floorf(zt));
			if (nextBlockY != NULL && nextBlockY->isSolid()) {
				velocity.y = 0;
				moveVector.y = roundf(yt) - (position.y + (c / 4 * ((box.halfDimentions.y * 2) + 0.001f)));
				if (nextPosition.y < position.y) {
					floorColl = true;
				} else {
					ceilColl = true;
				}

				break;
			} else {
				floorColl = ceilColl = false;
			}
		}
	}

	//Temp "falling off map" fix
	if (position.y < -64) {
		move(glm::vec3(0, 96, 0));
		velocity.y = 0;
	}
}

