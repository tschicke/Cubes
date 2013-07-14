/*
 * GUIElement.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: Tyler
 */

#include "GUIElement.h"

GUIElement::GUIElement() {
	x = y = 0;
	width = height = 0;

	needsUpdate = false;
}

GUIElement::GUIElement(int x, int y, int width, int height) {
	init(x, y, width, height);
}

GUIElement::GUIElement(int width, int height) {
	init(0, 0, width, height);
}

void GUIElement::init(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	needsUpdate = true;
}

GUIElement::~GUIElement() {
}

