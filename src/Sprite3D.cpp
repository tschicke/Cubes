/*
 * Sprite3D.cpp
 *
 *  Created on: Feb 2, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "GameWindow.h"
#include "Sprite3D.h"

using namespace glm;

Sprite3D::Sprite3D() {
	position = vec3(0, 0, 0);
	moveSpeed = 0;
	x = 0;//Temp
}

Sprite3D::Sprite3D(int x, int y, int z) {
	init(x, y, z);
}

void Sprite3D::init(int x, int y, int z) {
	position = vec3(x, y, z);

	Renderer::getMainRenderer().createMesh(&meshID);
	for (int x = 0; x < 32; x++){
		for(int y = 0; y < 128; y++){
			for(int z = 0; z < 32; z++){
				createCube(x, y, z);
			}
		}
	}
	Renderer::getMainRenderer().endMesh(&meshID);

	Shader vertexShader;
	vertexShader.loadShader("shaders/basicShader.vert", GL_VERTEX_SHADER);

	Shader fragmentShader;
	fragmentShader.loadShader("shaders/basicShader.frag", GL_FRAGMENT_SHADER);

	shaderProgram.createProgram();
	shaderProgram.addShader(&vertexShader);
	shaderProgram.addShader(&fragmentShader);
	shaderProgram.linkProgram();

	vertexShader.deleteShader();
	fragmentShader.deleteShader();
}

Sprite3D::~Sprite3D() {
}

void Sprite3D::setMoveDirection(int dx, int dy, int dz) {
	moveDirection = vec3(dx, dy, dz);
}

void Sprite3D::setPosition(int x, int y, int z) {
	position = vec3(x, y, z);
}

void Sprite3D::update(time_t dt) {
	position += (moveDirection * (float) (dt * moveSpeed)); //Move
	x += dt / 400.f;
	x = fmodf(x, 360.f);
}

void Sprite3D::draw(Renderer * renderer) {
	shaderProgram.useProgram();

	mat4 modelMatrix(1.f);
	mat4 viewMatrix = lookAt(vec3((20 * sinf(x)) + 16.5f, 16.5f, (20 * cosf(x)) + 15.5f), vec3(16.5f, 48.5f, 15.5f), vec3(0.f, 1.f, 0.f));
	mat4 projectionMatrix = perspective(90.f, 16.f / 9.f, 0.1f, 100.f);

	shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
	shaderProgram.setUniform("viewMatrix", &viewMatrix, 1);
	shaderProgram.setUniform("projectionMatrix", &projectionMatrix, 1);

	renderer->renderMesh(meshID);
}

//Temp

void Sprite3D::createCube(int x, int y, int z) {
	vec3 p1(x + 0, y + 0, z + 0);
	vec3 p2(x + 1, y + 0, z + 0);
	vec3 p3(x + 1, y + 1, z + 0);
	vec3 p4(x + 0, y + 1, z + 0);
	vec3 p5(x + 1, y + 0, z - 1);
	vec3 p6(x + 1, y + 1, z - 1);
	vec3 p7(x + 0, y + 0, z - 1);
	vec3 p8(x + 0, y + 1, z - 1);

	vec3 normal;

	float r = x / 32.f;
	float g = y / 128.f;
	float b = z / 32.f;

	int v1, v2, v3, v4, v5, v6, v7, v8;

	//Front
	normal = vec3(0, 0, 1);

	v1 = Renderer::getMainRenderer().addVertexToMesh(meshID, p1, normal, r, g, b);
	v2 = Renderer::getMainRenderer().addVertexToMesh(meshID, p2, normal, r, g, b);
	v3 = Renderer::getMainRenderer().addVertexToMesh(meshID, p3, normal, r, g, b);
	v4 = Renderer::getMainRenderer().addVertexToMesh(meshID, p4, normal, r, g, b);

	Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v2, v3);
	Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v3, v4);

	//Right
	normal = vec3(1, 0, 0);

	v2 = Renderer::getMainRenderer().addVertexToMesh(meshID, p2, normal, r, g, b);
	v3 = Renderer::getMainRenderer().addVertexToMesh(meshID, p3, normal, r, g, b);
	v5 = Renderer::getMainRenderer().addVertexToMesh(meshID, p5, normal, r, g, b);
	v6 = Renderer::getMainRenderer().addVertexToMesh(meshID, p6, normal, r, g, b);

	Renderer::getMainRenderer().addTriangleToMesh(meshID, v2, v3, v5);
	Renderer::getMainRenderer().addTriangleToMesh(meshID, v3, v5, v6);

	//Top
	normal = vec3(0, 1, 0);

	v3 = Renderer::getMainRenderer().addVertexToMesh(meshID, p3, normal, r, g, b);
	v4 = Renderer::getMainRenderer().addVertexToMesh(meshID, p4, normal, r, g, b);
	v6 = Renderer::getMainRenderer().addVertexToMesh(meshID, p6, normal, r, g, b);
	v8 = Renderer::getMainRenderer().addVertexToMesh(meshID, p8, normal, r, g, b);

	Renderer::getMainRenderer().addTriangleToMesh(meshID, v3, v4, v6);
	Renderer::getMainRenderer().addTriangleToMesh(meshID, v4, v6, v8);

	//Bottom
	normal = vec3(0, -1, 0);

	v1 = Renderer::getMainRenderer().addVertexToMesh(meshID, p1, normal, r, g, b);
	v2 = Renderer::getMainRenderer().addVertexToMesh(meshID, p2, normal, r, g, b);
	v5 = Renderer::getMainRenderer().addVertexToMesh(meshID, p5, normal, r, g, b);
	v7 = Renderer::getMainRenderer().addVertexToMesh(meshID, p7, normal, r, g, b);

	Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v2, v5);
	Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v5, v7);

	//Left
	normal = vec3(-1, 0, 0);

	v1 = Renderer::getMainRenderer().addVertexToMesh(meshID, p1, normal, r, g, b);
	v4 = Renderer::getMainRenderer().addVertexToMesh(meshID, p4, normal, r, g, b);
	v7 = Renderer::getMainRenderer().addVertexToMesh(meshID, p7, normal, r, g, b);
	v8 = Renderer::getMainRenderer().addVertexToMesh(meshID, p8, normal, r, g, b);

	Renderer::getMainRenderer().addTriangleToMesh(meshID, v1, v4, v7);
	Renderer::getMainRenderer().addTriangleToMesh(meshID, v4, v7, v8);

	//Back
	normal = vec3(0, 0, -1);

	v5 = Renderer::getMainRenderer().addVertexToMesh(meshID, p5, normal, r, g, b);
	v6 = Renderer::getMainRenderer().addVertexToMesh(meshID, p6, normal, r, g, b);
	v7 = Renderer::getMainRenderer().addVertexToMesh(meshID, p7, normal, r, g, b);
	v8 = Renderer::getMainRenderer().addVertexToMesh(meshID, p8, normal, r, g, b);

	Renderer::getMainRenderer().addTriangleToMesh(meshID, v5, v6, v7);
	Renderer::getMainRenderer().addTriangleToMesh(meshID, v6, v7, v8);
}
