/*
 * FirstPersonCamera.cpp
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#include <iostream>

#include <glm/gtx/transform.hpp>

#include "FirstPersonCamera.h"

using namespace glm;

FirstPersonCamera::FirstPersonCamera() {
}

FirstPersonCamera::~FirstPersonCamera() {
}

void FirstPersonCamera::update() {
	if (shouldUpdate) {
		viewMat = glm::lookAt(position, lookAt, vec3(0, 1, 0));
	}
	shouldUpdate = false;
}

void FirstPersonCamera::move(float x, float y, float z) {
	if (!(x == 0 && y == 0 && z == 0)) {
		vec3 flatPos; //position with no y component
		flatPos.x = position.x;
		flatPos.z = position.z;
		vec3 flatLook; //lookAt with no y component
		flatLook.x = lookAt.x;
		flatLook.z = lookAt.z;
		vec3 forward = glm::normalize(position - lookAt);
		vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
//		forward *= moveSpeed;
//		right *= moveSpeed;

		float moveX = (forward.x * z) + (right.x * x);
		float moveZ = (forward.z * z) + (right.z * x);

		position.x += moveX;
		lookAt.x += moveX;
		position.z += moveZ;
		lookAt.z += moveZ;

		position.y += y;
		lookAt.y += y;

		shouldUpdate = true;
	}
}

void FirstPersonCamera::look(int dx, int dy) {
	if (!(dx == 0 && dy == 0)) {
		yaw = fmodf(yaw, 360);
		yaw += dx * lookSpeed;

		if (pitch - (dy * lookSpeed) <= -89) {
			pitch = -89;
		} else if (pitch - (dy * lookSpeed) >= 89) {
			pitch = 89;
		} else {
			pitch -= dy * lookSpeed;
		}

		float yawR = toRadians(yaw), pitchR = toRadians(pitch);

		vec3 direction = position - lookAt;

		direction.x = sinf(yawR) * cosf(pitchR);
		direction.y = sinf(pitchR);
		direction.z = cosf(pitchR) * cosf(yawR);

		lookAt = position - direction;

		shouldUpdate = true;
	}
}

