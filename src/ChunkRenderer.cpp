/*
 * ChunkRenderer.cpp
 *
 *  Created on: May 18, 2013
 *      Author: Tyler
 */

#include "ChunkRenderer.h"
#include <gl/glew.h>

BaseRenderer::BaseRenderer() {
}

BaseRenderer::~BaseRenderer() {
}

//if vertexBuffer = true, GL_ARRAY_BUFFER, else GL_ELEMENT_ARRAY_BUFFER
uint BaseRenderer::createBufferWithSize(int size, bool vertexBuffer) {
	uint buffer;
	glGenBuffers(1, &buffer);
	int bufferToBind = (vertexBuffer ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(bufferToBind, buffer);
	glBufferData(bufferToBind, size, NULL, GL_STREAM_DRAW);
	glBindBuffer(bufferToBind, 0);

	return buffer;
}

void BaseRenderer::deleteBuffer(uint& buffer) {
	glDeleteBuffers(1, &buffer);
}

void BaseRenderer::substituteDataToVertexBuffer(uint bufferID, int size, int offset, float* data) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseRenderer::substituteDataToVertexBuffer(uint bufferID, int size, int offset, int* data) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseRenderer::substituteDataToIndexBuffer(uint bufferID, int size, int offset, int* data) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BaseRenderer::bindVertexBuffer(uint buffer) {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void BaseRenderer::bindIndexBuffer(uint buffer) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void BaseRenderer::unbindVertexBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseRenderer::unbindIndexBuffer() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BaseRenderer::render(){

}


