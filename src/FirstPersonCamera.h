/*
 * FirstPersonCamera.h
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#ifndef FIRSTPERSONCAMERA_H_
#define FIRSTPERSONCAMERA_H_

#include "Camera.h"

class FirstPersonCamera : public Camera{
public:
	FirstPersonCamera();
	virtual ~FirstPersonCamera();

	void look(int dx, int dy);
	glm::vec3 getMoveVector(float x, float y, float z);
	void update();
private:
};

#endif /* FIRSTPERSONCAMERA_H_ */
