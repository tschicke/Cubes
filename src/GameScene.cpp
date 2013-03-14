/*
 * GameScene.cpp
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "GameScene.h"

#include "Keyboard.h"
#include <SFML/Window/Mouse.hpp>

GameScene::GameScene() {

}

GameScene::~GameScene() {
}

void GameScene::handleInput() {
	int dx = 0, dy = 0;

	gameLayer.handleInput();

//	if (event.type == sf::Event::MouseMoved) {
//		dx = (1280 / 2) - event.mouseMove.x;
//		dy = (720 / 2) - event.mouseMove.y;
//	}
	gameLayer.updatePlayer(0, 0);
}

void GameScene::draw() {
	gameLayer.draw();
}

void GameScene::update(time_t dt) {
	gameLayer.update(dt);
}

