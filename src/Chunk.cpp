/*
 * Chunk.cpp
 *
 *  Created on: Feb 9, 2013
 *      Author: Tyler
 */
#include <iostream>

#include "Chunk.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"//Temp??
#include "glm/gtx/transform.hpp"//Temp??
#include "GameWindow.h"//Temp
#include <stdlib.h>
using namespace glm;
//Temp??

Chunk::Chunk() {
	init(0, 0, 0);
}

Chunk::Chunk(int x, int y, int z) {
	init(x, y, z);
}

void Chunk::init(int startX, int startY, int startZ) {
	//origin = vec3(x, y, z);
	meshID.setColorType(Texture);

	GameWindow::mainRenderer->createMesh(&meshID);

	blocks = new Block*[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				Block ** block = blockAt(x, y, z); //Change blockAt to return array index instead of Block **??
				int i = rand();
				if (i % 4 == 0) {
					*block = new BlockStone();
				} else if (i % 4 == 1) {
					*block = new BlockDirt();
				} else if (i % 4 == 2) {
					*block = new BlockGrass();
				} else {
					*block = new BlockGrass();
				}

				int height = x + z * 57 + y * 29;
				height = (height << 13) ^ height;
				height = 16 * (1.0 - ((height * (height * height * 15731 + 789221) + 1376312589) & 0X7fffffff) / 1073741824.0);

				if ((*block)->isDrawn()) {
					if (height <= 0) {
						createCube(x + startX, y + startY, z + startZ);
					}
				}
			}
		}
	}
	GameWindow::mainRenderer->endMesh(&meshID);

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

Chunk::~Chunk() {
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				delete blockAt(x, y, z);
			}
		}
	}
	delete[] blocks;
}

void Chunk::update(time_t dt) {
}

void Chunk::createCube(int x, int y, int z) {
	vec3 p1(x + 0, y + 0, z + 0);
	vec3 p2(x + 1, y + 0, z + 0);
	vec3 p3(x + 1, y + 1, z + 0);
	vec3 p4(x + 0, y + 1, z + 0);
	vec3 p5(x + 0, y + 0, z - 1);
	vec3 p6(x + 1, y + 0, z - 1);
	vec3 p7(x + 1, y + 1, z - 1);
	vec3 p8(x + 0, y + 1, z - 1);

	/*
	 *
	 * 		  p8__________p7
	 * 		   /|		 /|
	 * 		p4/_|_____p3/ |
	 * 		 |  |	   |  |
	 * 		 |	|p5____|__|p6
	 * 		 | /	   | /
	 * 	   p1|/________|/p2
	 */

	vec3 normal;

	Block ** block = blockAt(x, y, z);

//	float r = ((float) (rand() % 10)) / 10;//For colored cubes
//	float g = ((float) (rand() % 10)) / 10;//For colored cubes
//	float b = ((float) (rand() % 10)) / 10;//For colored cubes

	float u0 = 0, u1 = 0.5f, vv0 = 0.5f, vv1 = 1;

	int v1, v2, v3, v4, v5, v6, v7, v8;

	//Front
	normal = vec3(0, 0, 1);

	v1 = GameWindow::mainRenderer->addVertexToMesh(meshID, p1, normal, u0, vv0);
	v2 = GameWindow::mainRenderer->addVertexToMesh(meshID, p2, normal, u1, vv0);
	v3 = GameWindow::mainRenderer->addVertexToMesh(meshID, p3, normal, u1, vv1);
	v4 = GameWindow::mainRenderer->addVertexToMesh(meshID, p4, normal, u0, vv1);

	GameWindow::mainRenderer->addTriangleToMesh(meshID, v1, v2, v3);
	GameWindow::mainRenderer->addTriangleToMesh(meshID, v1, v3, v4);

	//Right
	normal = vec3(1, 0, 0);

	v2 = GameWindow::mainRenderer->addVertexToMesh(meshID, p2, normal, u0, vv0);
	v3 = GameWindow::mainRenderer->addVertexToMesh(meshID, p3, normal, u0, vv1);
	v6 = GameWindow::mainRenderer->addVertexToMesh(meshID, p6, normal, u1, vv0);
	v7 = GameWindow::mainRenderer->addVertexToMesh(meshID, p7, normal, u1, vv1);

	GameWindow::mainRenderer->addTriangleToMesh(meshID, v2, v6, v7);
	GameWindow::mainRenderer->addTriangleToMesh(meshID, v2, v7, v3);

	//Top
	normal = vec3(0, 1, 0);

	v3 = GameWindow::mainRenderer->addVertexToMesh(meshID, p3, normal, u1, vv0);
	v4 = GameWindow::mainRenderer->addVertexToMesh(meshID, p4, normal, u0, vv0);
	v7 = GameWindow::mainRenderer->addVertexToMesh(meshID, p7, normal, u1, vv1);
	v8 = GameWindow::mainRenderer->addVertexToMesh(meshID, p8, normal, u0, vv1);

	GameWindow::mainRenderer->addTriangleToMesh(meshID, v3, v7, v8);
	GameWindow::mainRenderer->addTriangleToMesh(meshID, v3, v8, v4);

	//Bottom
	normal = vec3(0, -1, 0);

	v1 = GameWindow::mainRenderer->addVertexToMesh(meshID, p1, normal, u0, vv1);
	v2 = GameWindow::mainRenderer->addVertexToMesh(meshID, p2, normal, u1, vv1);
	v5 = GameWindow::mainRenderer->addVertexToMesh(meshID, p5, normal, u0, vv0);
	v6 = GameWindow::mainRenderer->addVertexToMesh(meshID, p6, normal, u1, vv0);

	GameWindow::mainRenderer->addTriangleToMesh(meshID, v1, v5, v6);
	GameWindow::mainRenderer->addTriangleToMesh(meshID, v1, v6, v2);

	//Left
	normal = vec3(-1, 0, 0);

	v1 = GameWindow::mainRenderer->addVertexToMesh(meshID, p1, normal, u1, vv0);
	v4 = GameWindow::mainRenderer->addVertexToMesh(meshID, p4, normal, u1, vv1);
	v5 = GameWindow::mainRenderer->addVertexToMesh(meshID, p5, normal, u0, vv0);
	v8 = GameWindow::mainRenderer->addVertexToMesh(meshID, p8, normal, u0, vv1);

	GameWindow::mainRenderer->addTriangleToMesh(meshID, v1, v4, v8);
	GameWindow::mainRenderer->addTriangleToMesh(meshID, v1, v8, v5);

	//Back
	normal = vec3(0, 0, -1);

	v5 = GameWindow::mainRenderer->addVertexToMesh(meshID, p5, normal, u1, vv0);
	v6 = GameWindow::mainRenderer->addVertexToMesh(meshID, p6, normal, u0, vv0);
	v7 = GameWindow::mainRenderer->addVertexToMesh(meshID, p7, normal, u0, vv1);
	v8 = GameWindow::mainRenderer->addVertexToMesh(meshID, p8, normal, u1, vv1);

	GameWindow::mainRenderer->addTriangleToMesh(meshID, v5, v8, v7);
	GameWindow::mainRenderer->addTriangleToMesh(meshID, v5, v7, v6);
}

Block ** Chunk::blockAt(int x, int y, int z) {
	return &blocks[(x * CHUNK_SIZE * CHUNK_SIZE) + (y * CHUNK_SIZE) + z];
}

void Chunk::draw(Renderer * renderer) {
	shaderProgram.useProgram();
	Texture::grassTexture->useTexture();

	mat4 modelMatrix(1.f);
	mat4 viewMatrix = lookAt(vec3(20.f, (float) CHUNK_SIZE / 2, 10.f), vec3((float) CHUNK_SIZE / 2, (float) CHUNK_SIZE / 2, (float) CHUNK_SIZE / 2), vec3(0.f, 1.f, 0.f));

	shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
	shaderProgram.setUniform("viewMatrix", &viewMatrix, 1);
	shaderProgram.setUniform("projectionMatrix", Renderer::getProjectionMatrix(), 1);

	renderer->renderMesh(meshID);

	Texture::unbindTextures();
}

