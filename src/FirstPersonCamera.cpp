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

glm::vec3 FirstPersonCamera::getMoveVector(float dx, float dy, float dz) {
	glm::vec3 moveVector;
	if (dx || dy || dz) {
		glm::vec3 flatPosition(position.x, 0, position.z);
		glm::vec3 flatLookAt(lookAt.x, 0, lookAt.z);

		glm::vec3 forwardVector = glm::normalize(flatLookAt - flatPosition);
		glm::vec3 rightVector = glm::normalize(glm::cross(forwardVector, glm::vec3(0, 1, 0)));

		moveVector.x = rightVector.x * dx + forwardVector.x * dz;
		moveVector.y = dy;
		moveVector.z = rightVector.z * dx + forwardVector.z * dz;
	}
	return glm::normalize(moveVector);
}

void FirstPersonCamera::rotateWithMove(int dx, int dy) {
	yaw += (dx * lookSpeed);
	yaw = fmodf(yaw, 360);

	float newPitch = pitch + (dy * lookSpeed);
	if (newPitch > 89) {
		pitch = 89;
	} else if (newPitch < -89) {
		pitch = -89;
	} else {
		pitch = newPitch;
	}

	glm::vec3 lookDirection;

	float yawR = toRadians(yaw), pitchR = toRadians(pitch);

	lookDirection.x = sinf(yawR) * cosf(pitchR);
	lookDirection.y = sinf(pitchR);
	lookDirection.z = cosf(yawR) * cosf(pitchR);

	lookAt = position + lookDirection;
}

} /* namespace ts */

float toRadians(float degrees) {
	return (degrees * 3.141592) / 180.f;
}
