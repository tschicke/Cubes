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

protected:
	glm::vec3 velocity;
};

#endif /* DYNAMICENTITY_H_ */
