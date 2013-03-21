/*
 * FirstPersonCamera.h
 *
 *  Created on: Mar 21, 2013
 *      Author: Tyler
 */

#ifndef FIRSTPERSONCAMERA_H_
#define FIRSTPERSONCAMERA_H_

#include "Vectors.h"

namespace ts {

class FirstPersonCamera {
public:
	FirstPersonCamera();
	virtual ~FirstPersonCamera();

	ts::vec3 getMoveVector(int dx, int dy, int dz);

private:
	ts::vec3 position;
	int yaw, pitch;
};

} /* namespace ts */
#endif /* FIRSTPERSONCAMERA_H_ */
