/*
 * GameScene.cpp
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "GameScene.h"

#include "Keyboard.h"
#include "Mouse.h"

GameScene::GameScene() {
	ts::Mouse::setLocked(true);
}

GameScene::~GameScene() {
}

void GameScene::handleInput() {
	gameLayer.handleInput();

}

void GameScene::draw() {
	gameLayer.draw();
}

void GameScene::update(time_t dt) {
	gameLayer.update(dt);
}

