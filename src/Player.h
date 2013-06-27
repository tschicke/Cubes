/*
 * Player.h
 *
 *  Created on: Mar 3, 2013
 *      Author: Tyler
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"

#include "FirstPersonCamera.h"

#include "Renderer.h"
#include "Shader.h"

#include "SelectedBlock.h"

#include "Blocks/Block.h"

namespace ts {
class World;
}

class Player : public Character{
public:
	Player();
	Player(ts::World * world);
	virtual ~Player();

	void init(ts::World * world);

	void input();

	void update(time_t dt);

	void draw(glm::mat4 * viewMat);

	glm::vec3 getPosition();
	void setPosition(glm::vec3 newPos);

	glm::mat4 * getCameraViewMatrix(); //should be different??
private:
	ts::FirstPersonCamera camera;

	ts::World * world;

	glm::vec3 velocity;

	BlockType activeBlock;

	void gravity();
	float gravityStrength, gravityVel;
	bool onGround;

	void jump();
	float jumpStrength;

	void checkCollisions();

	void move(glm::vec3 moveVector); //On axis, not directional
	void move(float x, float y, float z); //On axis, not directional

	static const float CAMERA_HEIGHT = 1.5f, PLAYER_WIDTH = 0.75f, PLAYER_HEIGHT = 1.8f;
	float moveSpeed;

	MeshID playerModelID;
	ShaderProgram shaderProgram;

	void loadPlayerModel();
	bool loaded;

	SelectedBlock selectedBlock;
};

#endif /* PLAYER_H_ */
