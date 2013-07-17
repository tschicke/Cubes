/*
 * StringRenderer.cpp
 *
 *  Created on: Jul 16, 2013
 *      Author: Tyler
 */

#include "StringRenderer.h"

#include "SpriteSheet.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>

StringRenderer::StringRenderer() {
	allocLength = 8;
	numVertices = 0;
	numVerticesToDraw = 0;
	modelMatNeedsUpdate = false;

	x = y = 0;

	fontSize = 1;
}

StringRenderer::~StringRenderer() {
}

StringRenderer::StringRenderer(int x, int y, const char * string, int fontSize) {
	this->x = x;
	this->y = y;
	this->fontSize = fontSize;

	renderString = string;

	allocLength = 2;//TODO Fix this initialization

	modelMatNeedsUpdate = true;

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

	rebuildData();
}

void StringRenderer::rebuildData() {
	if (renderString.length() > allocLength) {
		glDeleteBuffers(1, &vertexBufferID);
		glDeleteBuffers(1, &indexBufferID);

		allocLength *= 2;

		int vertexBufferSize = allocLength * 4 * 4 * sizeof(float);
		int indexBufferSize = allocLength * 6 * sizeof(unsigned int);

		initBuffersWithSize(vertexBufferSize, indexBufferSize);
		std::cout << "test\n";
	}

	int vertexArrayLength = renderString.size() * 2 * 4;
	int textureArrayLength = renderString.size() * 2 * 4;
	int indexArrayLength = renderString.size() * 6;

	float * vertexData = new float[vertexArrayLength];
	float * texureData = new float[textureArrayLength];
	unsigned int * indexData = new unsigned int[indexArrayLength];

	float texSize = (float) ts::SpriteSheet::defaultFontSheet->getElementSizePixels() / ts::SpriteSheet::defaultFontSheet->getWidth();

	float letterVertexData[] = {
			0, 0,
			fontSize, 0,
			fontSize, fontSize,
			0, fontSize,
	};

	float letterTextureData[] = {
			0, texSize,
			texSize, texSize,
			texSize, 0,
			0, 0,
	};

	unsigned int letterIndexData[] = {
			0, 1, 2,
			0, 2, 3
	};

	for (unsigned int i = 0; i < renderString.size(); ++i) {
		int letterVertexIndex = i * 4 * 2;
		int letterIndexIndex = i * 6;

		float texOffsetX = ((renderString[i] - 'A') % ts::SpriteSheet::defaultFontSheet->numXElements()) / (float) ts::SpriteSheet::defaultFontSheet->numXElements();
		float texOffsetY = ((renderString[i] - 'A') / ts::SpriteSheet::defaultFontSheet->numYElements()) / (float) ts::SpriteSheet::defaultFontSheet->numYElements();

		for (int k = 0; k < 4; ++k) {
			vertexData[letterVertexIndex + (k * 2)] = letterVertexData[(k * 2)] + (i * fontSize);
			vertexData[letterVertexIndex + (k * 2) + 1] = letterVertexData[(k * 2) + 1];

			texureData[letterVertexIndex + (k * 2)] = letterTextureData[(k * 2)] + texOffsetX;
			texureData[letterVertexIndex + (k * 2) + 1] = letterTextureData[(k * 2) + 1] + texOffsetY;
		}

		for (int k = 0; k < 6; ++k) {
			indexData[letterIndexIndex + k] = letterIndexData[k] + (i * 4);
		}
	}

	substituteDataToVertexBuffer(sizeof(float) * vertexArrayLength, 0, vertexData);
	substituteDataToVertexBuffer(sizeof(float) * textureArrayLength, sizeof(float) * vertexArrayLength, texureData);
	substituteDataToIndexBuffer(sizeof(unsigned int) * indexArrayLength, 0, indexData);

	numVertices = renderString.size() * 4;
	numVerticesToDraw = renderString.size() * 6;

	delete vertexData;
	delete texureData;
	delete indexData;
}

void StringRenderer::render() {
	glDisable(GL_DEPTH_TEST);
	if (modelMatNeedsUpdate) {
		modelMatrix = glm::translate(glm::vec3(x, y, 0));
		modelMatNeedsUpdate = false;
	}

	shaderProgram.useProgram();

	ts::SpriteSheet::defaultFontSheet->useTexture();

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

void StringRenderer::setString(const char* string) {
	renderString = string;
	rebuildData();
}

void StringRenderer::appendToString(const char* string, int numChars) {
	for (int i = 0; i < numChars; ++i) {
		renderString.append(string + i);
	}
	rebuildData();
}

int StringRenderer::getWidthOfString(const char* string, int fontSize) {
	std::string s = string;
	return (s.size() * fontSize);
}
