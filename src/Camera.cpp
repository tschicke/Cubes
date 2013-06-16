/*
 * Camera.cpp
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#include "Camera.h"

using namespace glm;

Camera::Camera() {
	yaw = 180;
	pitch = 0;
	lookSpeed = 0.2f;
	inverted = 1;
	shouldUpdate = false;
	position = vec3(0, 0, 0);
	lookAt = vec3(0, 0, -1);
}

void Camera::setPosition(vec3 newPos){
	vec3 diffVec = newPos - position;
	position += diffVec;
	lookAt += diffVec;
}

Camera::~Camera() {
}

glm::vec3 Camera::getLook() {
	return lookAt;
}

float Camera::toRadians(float deg){
	return (deg * 3.141592) / 180;
}

vec3 Camera::getPosition(){
	return position;
}

int Camera::getYaw(){
	return yaw;
}

mat4* Camera::getViewMatrix(){
	return &viewMat;
}
