/*
 * DynamicEntity.h
 *
 *  Created on: Jun 30, 2013
 *      Author: Tyler
 */

#ifndef DYNAMICENTITY_H_
#define DYNAMICENTITY_H_

#include "Entity.h"

class DynamicEntity: public Entity {
public:
	DynamicEntity();
	DynamicEntity(ts::World * world, glm::vec3 position);
	DynamicEntity(ts::World * world, glm::vec3 position, glm::vec3 velocity);
	virtual ~DynamicEntity();

	void init(ts::World * world, glm::vec3 position, glm::vec3 velocity);

	virtual void move(glm::vec3 moveVec);

	void update(time_t dt);

	void addYaw(float yaw);
	void addPitch(float pitch);

	void checkCollisions();

protected:
	glm::vec3 velocity, moveVector;

	bool affectedByGravity;

	bool xColl, zColl, ceilColl, floorColl;
};

#endif /* DYNAMICENTITY_H_ */
