/*
 * GameScene.cpp
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "GameScene.h"

#include "GameWindow.h"

#include "MenuScene.h"

#include "Keyboard.h"
#include "Mouse.h"

GameScene::GameScene() {
	ts::Mouse::setLocked(true);

	hud.setParentScene(this);
	gameLayer.setParentScene(this);
}

GameScene::~GameScene() {
}

void GameScene::handleInput() {
	if(ts::Keyboard::checkKeyEvent(ts::Keyboard::M) == ts::Keyboard::keyPressed){
		GameWindow::getMainWindow()->setScene(new MenuScene);
	}

	gameLayer.handleInput();

}

void GameScene::draw() {
	gameLayer.draw();
	hud.draw();
}

void GameScene::update(time_t dt) {
	hud.update(dt);
	gameLayer.update(dt);
}

GameLayer* GameScene::getGameLayer() {
	return &gameLayer;
}

HudLayer* GameScene::getHudLayer() {
	return &hud;
}
