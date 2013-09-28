/*
 * ChunkRenderer.cpp
 *
 *  Created on: May 18, 2013
 *      Author: Tyler
 */

#include "BaseRenderer.h"
#include <gl/glew.h>

#include <glm/gtx/transform.hpp>

#include <iostream>

float BaseRenderer::fov = 90.f;
glm::mat4 BaseRenderer::projectionMatrix = glm::perspective(fov, 600.f / 400.f, 0.1f, 100.f);
glm::mat4 BaseRenderer::orthoMatrix;

BaseRenderer::BaseRenderer() {
	vertexBufferID = -1;
	indexBufferID = -1;
	vertBuffLoaded = false;
	indexBuffLoaded = false;
}

BaseRenderer::~BaseRenderer() {
	deleteBuffers();
	shaderProgram.deleteProgram();
}

void BaseRenderer::initBuffersWithSize(int vertexBufferSize, int indexBufferSize) {
	if (!vertBuffLoaded) {
		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		vertBuffLoaded = true;
	}

	if (!indexBuffLoaded) {
		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		indexBuffLoaded = true;
	}
}

void BaseRenderer::deleteBuffers() {
	if (vertBuffLoaded) {
		glDeleteBuffers(1, &vertexBufferID);
		vertexBufferID = -1;
		vertBuffLoaded = false;
	}

	if (indexBuffLoaded) {
		glDeleteBuffers(1, &indexBufferID);
		indexBufferID = -1;
		indexBuffLoaded = false;
	}
}

void BaseRenderer::substituteDataToVertexBuffer(int size, int offset, float* data) {
	if (vertBuffLoaded) {
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void BaseRenderer::substituteDataToVertexBuffer(int size, int offset, int* data) {
	if (vertBuffLoaded) {
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void BaseRenderer::substituteDataToIndexBuffer(int size, int offset, unsigned int* data) {
	if (indexBuffLoaded) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void BaseRenderer::bindVertexBuffer() {
	if (vertBuffLoaded) {
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	}
}

void BaseRenderer::bindIndexBuffer() {
	if (indexBuffLoaded) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferID);
	}
}

void BaseRenderer::unbindVertexBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseRenderer::unbindIndexBuffer() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BaseRenderer::translateModelMatrix(float x, float y, float z) {
	modelMatrix *= glm::translate(x, y, z);
}

void BaseRenderer::setProjectionMatrix() {
}

void BaseRenderer::setOrthoMatrix(int width, int height) {
	orthoMatrix = glm::ortho(0.f, (float) width, 0.f, (float) height, -1.f, 1.f);
}
