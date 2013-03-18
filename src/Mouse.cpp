/*
 * Mouse.cpp
 *
 *  Created on: Mar 16, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "Mouse.h"

namespace ts {

glm::vec2 Mouse::position;
bool Mouse::locked;
int Mouse::lastDX, Mouse::lastDY;

Mouse::Mouse() {
}

Mouse::~Mouse() {
}

void Mouse::init(){
	locked = false;
	lastDX = 0;
	lastDY = 0;
}

void Mouse::setPosition(int x, int y){
	position = glm::vec2(x, y);
}

glm::vec2 Mouse::getPosition(){
	return position;
}

void Mouse::movePosition(int dx, int dy){
	position += glm::vec2(dx, dy);
}

void Mouse::setLastMove(int dx, int dy){
	lastDX = dx;
	lastDY = dy;
}

glm::vec2 Mouse::getLastMove(){
	return glm::vec2(lastDX, lastDY);
}

void Mouse::setLocked(bool isLocked){
	locked = isLocked;
}

bool Mouse::isLocked(){
	return locked;
}

} /* namespace ts */
