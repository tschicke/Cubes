/*
 * HudLayer.cpp
 *
 *  Created on: Jun 16, 2013
 *      Author: Tyler
 */

#include "HudLayer.h"

#include <gl/glew.h>

HudLayer::HudLayer() {
	glLineWidth(2);
	button = GUIButton(400, 300, 100, 100);
}

HudLayer::~HudLayer() {
}

void HudLayer::draw() {
	glDisable(GL_DEPTH_TEST);
	button.draw();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -1, 1);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(390, 300);
	glVertex2f(410, 300);
	glVertex2f(400, 290);
	glVertex2f(400, 310);
	glEnd();

	glEnable(GL_DEPTH_TEST);
}

void HudLayer::update(time_t dt) {
	button.update();
}

void HudLayer::handleInput() {
}
