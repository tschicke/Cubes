/*
 * ChunkRenderer.cpp
 *
 *  Created on: May 19, 2013
 *      Author: Tyler
 */

#include "ChunkRenderer.h"

#include "Chunk.h"
#include "Player.h"

#include <gl/glew.h>

ChunkRenderer::ChunkRenderer() {
	Shader vertexShader;
	vertexShader.loadShader("shaders/textureShader.vert", GL_VERTEX_SHADER);

	Shader fragmentShader;
	fragmentShader.loadShader("shaders/textureShader.frag", GL_FRAGMENT_SHADER);

	ShaderProgram shaderProgram;
	shaderProgram.createProgram();
	shaderProgram.addShader(&vertexShader);
	shaderProgram.addShader(&fragmentShader);
	shaderProgram.linkProgram();

	vertexShader.deleteShader();
	fragmentShader.deleteShader();
}

ChunkRenderer::~ChunkRenderer() {
}

void ChunkRenderer::render(Player * player) {
	shaderProgram.useProgram();

	//Bind Texture

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	shaderProgram.setUniform("modelMatrix", &modelMatrix);
	shaderProgram.setUniform("viewMatrix", player->getCameraViewMatrix());
	shaderProgram.setUniform("projectionMatrix", &projectionMatrix);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	int numCubes = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * 36;
	int numVertices = numCubes * 24;
	int numIndices = numCubes * 36;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); //Vertices
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) (numVertices * 3)); //Texture Coordinates
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) (numVertices * 5));//Normals

	glDrawElements(GL_TRIANGLES, numIndices, GL_FLOAT, (void *) 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Unbind Texture
}

