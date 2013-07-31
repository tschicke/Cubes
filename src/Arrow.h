/*
 * Arrow.h
 *
 *  Created on: Jul 30, 2013
 *      Author: Tyler
 */

#ifndef ARROW_H_
#define ARROW_H_

#include "DynamicEntity.h"

class Arrow: public DynamicEntity {
public:
	Arrow();
	Arrow(ts::World * parentWorld, glm::vec3 position, glm::vec3 velocity);

	virtual ~Arrow();

	void update(time_t dt);

	const char * getModelPath();
};

#endif /* ARROW_H_ */
