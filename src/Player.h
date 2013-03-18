/*
 * Player.h
 *
 *  Created on: Mar 3, 2013
 *      Author: Tyler
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <glm/glm.hpp>

#include "Common.h"

#include "FirstPersonCamera.h"

enum MovementState {
	forward, back, left, right, up, down, movementStatesCount//Up and down are temp/noclip
};

class Player {
public:
	Player();
	virtual ~Player();


	void update(time_t dt);

	void setMovementState(MovementState state, bool value);
	void setLookStates(int dx, int dy);
	void jump();

	void setPosition(glm::vec3 newPosition);//Should be private?
	glm::vec3 getPosition();//Should be private?

	void setYaw(int newYaw);//Should be private?

	FirstPersonCamera* getMainCamera();
private:
	glm::vec3 position;
	float yaw;

	void move();
	void look();

	void gravity();
	const float gravityStrength;
	float gravityDY;

	bool inAir;
	void setInAir();
	bool isInAir();

	void checkCollisions();

	float moveSpeed, jumpStrength;

	bool movementStates[movementStatesCount];
	int lookDX, lookDY;

	int height;

	FirstPersonCamera mainCamera;
};

#endif /* PLAYER_H_ */
