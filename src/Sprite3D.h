/*
 * Sprite3D.h
 *
 *  Created on: Feb 2, 2013
 *      Author: Tyler
 */

#ifndef SPRITE3D_H_
#define SPRITE3D_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Drawable.h"
#include "Common.h"
#include "Shader.h"

class Sprite3D: public Drawable {
public:
	Sprite3D();
	Sprite3D(int x, int y, int z);
	virtual ~Sprite3D();
	void init(int x, int y, int z);

	void update(time_t dt);
	void draw(Renderer * renderer);

	void setMoveDirection(int dx, int dy, int dz);
	void setPosition(int x, int y, int z);
protected:
	//New OpenGL stuff
	MeshID meshID;

	ShaderProgram shaderProgram;

	//Sprite Stuff
	glm::vec3 position, moveDirection;
	int moveSpeed;


	//Temp
	void createCube(int x, int y, int z);
	float x;
};

#endif /* SPRITE3D_H_ */
