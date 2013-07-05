/*
 * CollisionBox.h
 *
 *  Created on: Jul 3, 2013
 *      Author: Tyler
 */

#ifndef COLLISIONBOX_H_
#define COLLISIONBOX_H_

#include <glm/glm.hpp>

struct CollisionBox {
public:
	CollisionBox();
	CollisionBox(glm::vec3 position, glm::vec3 halfDimentions);
	virtual ~CollisionBox();

	glm::vec3 position, halfDimentions;
};

#endif /* COLLISIONBOX_H_ */
