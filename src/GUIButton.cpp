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

GUIButton::GUIButton(int width, int height)
:GUIElement(width, height){
	pressed = false;
	renderer.setCurrentTexture(Texture::buttonDefault);
}

GUIButton::GUIButton(int x, int y, int width, int height)
:GUIElement(x, y, width, height){
	pressed = false;
	renderer.setCurrentTexture(Texture::buttonDefault);
}

GUIButton::~GUIButton() {
}

void GUIButton::update() {
	glm::vec2 mousePos = ts::Mouse::getPosition();
	bool isMouseInBounds = isPointInBounds(mousePos);

	if(isMouseInBounds){
		if(ts::Mouse::isButtonPressed(ts::Mouse::Button0)){
			renderer.setCurrentTexture(Texture::buttonPressed);
		} else {
			renderer.setCurrentTexture(Texture::buttonMouseOver);
		}

		if(ts::Mouse::checkMouseButtonEvent(ts::Mouse::Button0) == ts::Mouse::buttonReleased){
			pressed = true;
		}
	} else {
		renderer.setCurrentTexture(Texture::buttonDefault);
	}
}

bool GUIButton::wasPressed() {
	return pressed;
}
