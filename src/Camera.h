/*
 * Camera.h
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>

class Camera {
public:
	Camera();
	virtual ~Camera();

	virtual void move(float x, float y, float z) = 0;
	virtual void look(int dx, int dy) = 0;

	void setPosition(glm::vec3 newPos);
	glm::vec3 getPosition();

	glm::vec3 getLook();

	int getYaw();

	glm::mat4* getViewMatrix();

protected:
	glm::vec3 position, lookAt;
	glm::mat4 viewMat;
	short inverted; //future
	float lookSpeed;
	float yaw, pitch;
	float toRadians(float deg);
	virtual void update() = 0;
	bool shouldUpdate;
};

#endif /* CAMERA_H_ */
