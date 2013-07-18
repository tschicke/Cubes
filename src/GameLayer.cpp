/*
 * GameLayer.cpp
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "GameLayer.h"

#include "Keyboard.h"
#include "Mouse.h"

#include "MainWorld.h"

GameLayer::GameLayer() {
	world = new ts::MainWorld;
}

GameLayer::~GameLayer() {
}

void GameLayer::update(time_t dt) {
	world->update(dt);
}

void GameLayer::handleInput() {
	world->handleInput();
}

void GameLayer::draw() {
	world->draw();
}

Player* GameLayer::getWorldMainPlayer() {
	return world->getMainPlayer();
}
