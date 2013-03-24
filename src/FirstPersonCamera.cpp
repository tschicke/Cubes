/*
 * FirstPersonCamera.cpp
 *
 *  Created on: Mar 21, 2013
 *      Author: Tyler
 */

#include "FirstPersonCamera.h"

namespace ts {

FirstPersonCamera::FirstPersonCamera() {
	init(glm::vec3(0, 0, 0));
}

FirstPersonCamera::FirstPersonCamera(glm::vec3 position) {
	init(position);
}

void FirstPersonCamera::init(glm::vec3 position) {
	yaw = 0;
	pitch = 0;
	this->position = position;
	lookAt = position + glm::vec3(0, 0, 1); //might need to be -1
}

FirstPersonCamera::~FirstPersonCamera() {
}

void FirstPersonCamera::setPosition(glm::vec3 newPosition) {
	glm::vec3 moveVector = newPosition - position;
	position += moveVector;
	lookAt += moveVector;
}

void FirstPersonCamera::move(int x, int y, int z) {
	glm::vec3 moveVector(x, y, z);
	position += moveVector;
	lookAt += moveVector;
}

void FirstPersonCamera::move(glm::vec3 moveVector) {
	position += moveVector;
	lookAt += moveVector;
}

glm::vec3 FirstPersonCamera::getMoveVector(int dx, int dy, int dz) {
	glm::vec3 moveVector;

}

void FirstPersonCamera::rotateWithMove(int dx, int dy) {
	yaw += dx;
	yaw = fmodf(yaw, 360);

	float newPitch = pitch + (dy * lookSpeed);
	if (newPitch > 89) {
		pitch = 89;
	} else if (newPitch < -89) {
		pitch = -89;
	} else {
		pitch = newPitch;
	}
}

} /* namespace ts */
