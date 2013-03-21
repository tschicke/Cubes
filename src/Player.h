/*
 * Player.h
 *
 *  Created on: Mar 3, 2013
 *      Author: Tyler
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Vectors.h"

#include "Common.h"

#include "FirstPersonCamera.h"

class Player {
public:
	Player();
	virtual ~Player();

	void input();

	void update(time_t dt);

//	void draw();

	ts::vec3<float> getPosition();
	void setPosition(ts::vec3<float> newPos);
private:
	FirstPersonCamera camera;

	ts::vec3<float> position, moveVector;
	float yaw, pitch;

	void jump();

	static const float height;
};

#endif /* PLAYER_H_ */
