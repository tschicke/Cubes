/*
 * GUIRenderer.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: Tyler
 */

#include "GUIRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "GUIElement.h"

#include <iostream>

GUIRenderer::GUIRenderer() {
	numVertices = 0;
	numVerticesToDraw = 0;
	parentElement = NULL;
	modelMatNeedsUpdate = false;

	currentTexture = Texture::buttonDefault;//Should be button by default?
}

GUIRenderer::~GUIRenderer() {
}

void GUIRenderer::init(GUIElement* parentElement, Texture * texture) {
	this->parentElement = parentElement;

	numVertices = 4;
	numVerticesToDraw = 6;

	Shader vertexShader;
	vertexShader.loadShader("shaders/guiShader.vert", GL_VERTEX_SHADER);

	Shader fragmentShader;
	fragmentShader.loadShader("shaders/guiShader.frag", GL_FRAGMENT_SHADER);

	shaderProgram.createProgram();
	shaderProgram.addShader(&vertexShader);
	shaderProgram.addShader(&fragmentShader);
	shaderProgram.linkProgram();

	vertexShader.deleteShader();
	fragmentShader.deleteShader();

	initBuffersWithSize(sizeof(float) * numVertices * 2 * 2, sizeof(unsigned int) * numVerticesToDraw);
	int width = parentElement->width, height = parentElement->height;
	float vertexData[] = {
			0, 0,
			width, 0,
			width, height,
			0, height,

			0, 0,
			1, 0,
			1, 1,
			0, 1
	};
	unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
	};
	substituteDataToVertexBuffer(sizeof(vertexData), 0, vertexData);
	substituteDataToIndexBuffer(sizeof(indices), 0, indices);

	modelMatNeedsUpdate = true;

	currentTexture = texture;
}

void GUIRenderer::setCurrentTexture(Texture* texture) {
	currentTexture = texture;
}

void GUIRenderer::render() {
	glDisable(GL_DEPTH_TEST);
	if (modelMatNeedsUpdate) {
		modelMatrix = glm::translate(glm::vec3(parentElement->x, parentElement->y, 0));
		modelMatNeedsUpdate = false;
	}

	shaderProgram.useProgram();

	currentTexture->useTexture();

	shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
	shaderProgram.setUniform("projectionMatrix", &orthoMatrix, 1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0); //Vertices
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) (sizeof(float) * numVertices * 2)); //TexCoords

	glDrawElements(GL_TRIANGLES, numVerticesToDraw, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(0);
	glEnable(GL_DEPTH_TEST);
}
