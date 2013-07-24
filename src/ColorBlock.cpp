/*
 * ColorBlock.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: Tyler
 */

#include "ColorBlock.h"

ColorBlock::ColorBlock() {
	drawn = false;
}

ColorBlock::~ColorBlock() {
	// TODO Auto-generated destructor stub
}

void ColorBlock::setDrawn(bool drawn) {
	this->drawn = drawn;
}

bool ColorBlock::isDrawn() {
	return drawn;
}

void ColorBlock::setColor(glm::vec3 color) {
	this->color = color;
}

glm::vec3 ColorBlock::getColor() {
	return color;
}
