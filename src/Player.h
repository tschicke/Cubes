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

class Player {
public:
	Player();
	virtual ~Player();

	void input();

	void update(time_t dt);

//	void draw();

	glm::vec3 getPosition();
	void setPosition(glm::vec3 newPos);
private:
	ts::FirstPersonCamera camera;

	glm::vec3 position, moveVector;
	float yaw, pitch;

	void jump();

	static const float playerHeight;
};

#endif /* PLAYER_H_ */
