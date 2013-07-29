/*
 * Entity.h
 *
 *  Created on: Jun 29, 2013
 *      Author: Tyler
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <glm/glm.hpp>

#include "Common.h"

#include "CubeModel.h"

#include "CollisionBox.h"

namespace ts {
class World;
}

class Entity {
public:
	Entity();
	Entity(ts::World * world, glm::vec3 position);
	virtual ~Entity();

	void init(ts::World * world, glm::vec3 position);

	virtual void update(time_t dt) = 0;
	virtual void draw(); //TODO should be virtual?

	friend class CubeModel;
	friend class EntityRenderer; //Temp

	virtual const char * getModelPath();

	CollisionBox getCollisionBox();

	glm::vec3 getPosition();
	virtual void setPosition(glm::vec3 position);

	bool shouldBeDeleted();
	void deleteEntity();

	int getYaw();
	int getPitch();

	void setYaw(int yaw);
	void setPitch(int pitch);
	void incrementYaw(int delta);
	void incrementPitch(int delta);
protected:
	glm::vec3 position;
	glm::vec3 halfDimentions; //TODO why is this half dimentions instead of full dimentions
	int yaw, pitch;

	ts::World * parentWorld;

	CubeModel model;

	bool flagShouldBeDeleted;
};

#endif /* ENTITY_H_ */
