/*
 * Character.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Tyler
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Common.h"

#include <glm/glm.hpp>

class Character {
public:
	Character();
	virtual ~Character();

	virtual void update(time_t dt) = 0;
	virtual void draw(glm::mat4 * viewMatrix) = 0;

protected:
	glm::vec3 position, moveVector;
	float yaw, pitch;
};

#endif /* CHARACTER_H_ */
