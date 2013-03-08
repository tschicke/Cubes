/*
 * Player.h
 *
 *  Created on: Mar 3, 2013
 *      Author: Tyler
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <glm/glm.hpp>

#include "FirstPersonCamera.h"

enum movementDirections {
	forward, back, left, right, up, down, movementStatesCount//Up and down are temp/noclip
};

class Player {
public:
	Player();
	virtual ~Player();

	void update();

	void setPosition(glm::vec3 newPosition);//Should be private?
	glm::vec3 getPosition();//Should be private?

	void setYaw(int newYaw);//Should be private?

	void look(int dx, int dy);

	void setMovementState(int state, bool value);

	FirstPersonCamera* getMainCamera();
private:
	glm::vec3 position;
	float yaw;

	void move();

	float moveSpeed;

	bool movementStates[movementStatesCount];

	FirstPersonCamera mainCamera;
};

#endif /* PLAYER_H_ */
