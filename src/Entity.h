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

class Entity {//TODO gravity and collisions
public:
	Entity();
	Entity(ts::World * world, glm::vec3 position);
	virtual ~Entity();

	void init(ts::World * world, glm::vec3 position);

	virtual void update(time_t dt) = 0;
	virtual void draw();

	friend class EntityRenderer;
protected:
	glm::vec3 position;
	float yaw, pitch;

	ts::World * parentWorld;

	EntityRenderer renderer;
};

#endif /* ENTITY_H_ */
