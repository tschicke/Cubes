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

#include "EntityRenderer.h"

namespace ts{
class World;
}

class Entity {
public:
	Entity();
	Entity(ts::World * world, float x, float y, float z);
	Entity(ts::World * world, glm::vec3 position);
	virtual ~Entity();

	void init(ts::World * world, glm::vec3 position);

	virtual void update(time_t dt){};
	void draw();

	void move(float x, float y, float z);
	void move(glm::vec3 moveVec);

	void addYaw(float yaw);
	void addPitch(float pitch);

	friend class EntityRenderer;
protected:
	glm::vec3 position;
	float yaw, pitch;

	ts::World * parentWorld;

	EntityRenderer renderer;
};

#endif /* ENTITY_H_ */
