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

#include "Renderer.h"
#include "Shader.h"

class Player {
public:
	Player();
	virtual ~Player();

	void input();

	void update(time_t dt);

	void draw(glm::mat4 * viewMat);

	glm::vec3 getPosition();
	void setPosition(glm::vec3 newPos);

	glm::mat4 * getCameraViewMatrix();//should be different??
private:
	ts::FirstPersonCamera camera;

	glm::vec3 position, moveVector;
	float yaw, pitch;

	void jump();

	void move(glm::vec3 moveVector);//On axis, not directional
	void move(float x, float y, float z);//On axis, not directional

	static const float playerHeight;
	float moveSpeed;

	MeshID playerModelID;
	ShaderProgram shaderProgram;

	void loadPlayerModel();
};

#endif /* PLAYER_H_ */
