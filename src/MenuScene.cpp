/*
 * MenuScene.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: Tyler
 */

#include "MenuScene.h"
#include "GameScene.h"

#include "GameWindow.h"

#include "Mouse.h"

MenuScene::MenuScene() {
	ts::Mouse::setLocked(false);

	playButton.init(540, 310, 200, 100, "PLAY");
	closeButton.init(540, 160, 200, 100, "EXIT");
}

MenuScene::~MenuScene() {
}

void MenuScene::handleInput() {
}

void MenuScene::update(time_t dt) {
	playButton.update();
	closeButton.update();

	if(playButton.wasPressed()){
		GameWindow::getMainWindow()->setScene(new GameScene);
	}

	if(closeButton.wasPressed()){
		GameWindow::getMainWindow()->stop();
	}
}

void MenuScene::draw() {
	playButton.draw();
	closeButton.draw();
}
