/*
 * Character.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Tyler
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Common.h"

#include "DynamicEntity.h"

#include <glm/glm.hpp>

class Character : public DynamicEntity{
public:
	Character();
	virtual ~Character();

	virtual void update(time_t dt) = 0;
protected:
	float yaw, pitch;
};

#endif /* CHARACTER_H_ */
