/*
 * HudLayer.cpp
 *
 *  Created on: Jun 16, 2013
 *      Author: Tyler
 */

#include "HudLayer.h"

#include <gl/glew.h>

#include <sstream>

#include "Player.h"

#include "GameScene.h"

HudLayer::HudLayer() {
	glLineWidth(2);
//	button = GUIButton(50, 50, 200, 200);
	/*The issue is that GUIRenderer's parent is being set to the address of GUIButton(50, 50, 200, 200),
	 *  while button is just a copy of GUIButton(50, 50, 200, 200), at a different address*/

	std::stringstream formattedString;
	formattedString.precision(2);
	formattedString << std::fixed << 0 << ' ' << 0 << ' ' << 0;
	playerPosString = StringRenderer(16, 688, formattedString.str().c_str(), 32);
}

HudLayer::~HudLayer() {
}

void HudLayer::draw() {
//	glDisable(GL_DEPTH_TEST);

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

	playerPosString.render();
}

void HudLayer::update(time_t dt) {
	Player * mainPlayer = parentScene->getGameLayer()->getWorldMainPlayer();
	glm::vec3 playerPos = mainPlayer->getPosition();
	std::stringstream formattedString;
	formattedString.precision(2);
	formattedString << std::fixed << playerPos.x << ' ' << playerPos.y << ' ' << playerPos.z;
	playerPosString.setString(formattedString.str().c_str());
}

void HudLayer::handleInput() {
}
