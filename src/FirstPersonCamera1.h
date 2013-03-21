/*
 * FirstPersonCamera.h
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#ifndef FIRSTPERSONCAMERA_H_
#define FIRSTPERSONCAMERA_H_

#include "Camera.h"

class FirstPersonCamera1 : public Camera{
public:
	FirstPersonCamera1();
	virtual ~FirstPersonCamera1();

	void look(int dx, int dy);
	void move(float x, float y, float z);
	void update();
private:
};

#endif /* FIRSTPERSONCAMERA_H_ */
