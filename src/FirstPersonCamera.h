/*
 * FirstPersonCamera.h
 *
 *  Created on: Mar 21, 2013
 *      Author: Tyler
 */

#ifndef FIRSTPERSONCAMERA_H_
#define FIRSTPERSONCAMERA_H_

#include <glm/glm.hpp>

namespace ts {

class FirstPersonCamera {
public:
	FirstPersonCamera();
	FirstPersonCamera(glm::vec3 position);
	virtual ~FirstPersonCamera();
	void init(glm::vec3 position);

	void setPosition(glm::vec3 newPosition);

	glm::vec3 getMoveVector(float dx, float dy, float dz);
	void rotateWithMove(int dx, int dy);

	void move(int x, int y, int z);
	void move(glm::vec3 moveVector);

	glm::mat4 * getViewMatrix();

private:
	glm::vec3 position, lookAt;
	glm::mat4 viewMatrix;//Temp??
	float yaw, pitch;
	float lookSpeed;

	float toRadians(float degrees);

	bool flag_shouldUpdate;
};

} /* namespace ts */
#endif /* FIRSTPERSONCAMERA_H_ */
