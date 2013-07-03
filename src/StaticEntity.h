/*
 * StaticEntity.h
 *
 *  Created on: Jun 30, 2013
 *      Author: Tyler
 */

#ifndef STATICENTITY_H_
#define STATICENTITY_H_

#include "Entity.h"

class StaticEntity : public Entity{
public:
	StaticEntity();
	virtual ~StaticEntity();

	void update(time_t dt);
};

#endif /* STATICENTITY_H_ */
