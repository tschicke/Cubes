/*
 * GUIButton.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: Tyler
 */

#include "GUIButton.h"

#include "Mouse.h"

#include <iostream>

GUIButton::GUIButton() {
	pressed = false;
	renderer.setCurrentTexture(Texture::buttonDefault);
}

GUIButton::GUIButton(int width, int height, const char * string) {
	init(0, 0, width, height, string);
}

GUIButton::GUIButton(int x, int y, int width, int height, const char * string) {
	init(x, y, width, height, string);
}

void GUIButton::init(int x, int y, int width, int height, const char* string) {
	GUIElement::init(x, y, width, height);
	pressed = false;
	renderer.setCurrentTexture(Texture::buttonDefault);

	int stringWidth = StringRenderer::getWidthOfString(string, 32);
	buttonString = StringRenderer(((width - stringWidth) / 2) + x, ((height - 32) / 2) + y, string, 32);
}

GUIButton::~GUIButton() {
}

void GUIButton::update() {
	glm::vec2 mousePos = ts::Mouse::getPosition();
	bool isMouseInBounds = isPointInBounds(mousePos);

	if (isMouseInBounds) {
		if (ts::Mouse::isButtonPressed(ts::Mouse::Button0)) {
			renderer.setCurrentTexture(Texture::buttonPressed);
		} else {
			renderer.setCurrentTexture(Texture::buttonMouseOver);
		}

		if (ts::Mouse::checkMouseButtonEvent(ts::Mouse::Button0) == ts::Mouse::buttonReleased) {
			pressed = true;
		}
	} else {
		renderer.setCurrentTexture(Texture::buttonDefault);
	}
}

void GUIButton::draw() {
	GUIElement::draw();
	buttonString.render();
}

bool GUIButton::wasPressed() {
	return pressed;
}
