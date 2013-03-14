/*
 * GameScene.cpp
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "GameScene.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

GameScene::GameScene() {

}

GameScene::~GameScene() {
}

void GameScene::handleEvent(sf::Event event) {
	int dx = 0, dy = 0;
	if (event.type == sf::Event::KeyPressed) {
		std::cout << event.key.code << std::endl;
		if (event.key.code == sf::Keyboard::A) {
			gameLayer.setPlayerMoveState(left, true);
		} else if (event.key.code == sf::Keyboard::D) {
			gameLayer.setPlayerMoveState(right, true);
		} else if (event.key.code == sf::Keyboard::W) {
			gameLayer.setPlayerMoveState(forward, true);
		} else if (event.key.code == sf::Keyboard::S) {
			gameLayer.setPlayerMoveState(back, true);
		} else if (event.key.code == sf::Keyboard::Q) {
			gameLayer.setPlayerMoveState(up, true);
		} else if (event.key.code == sf::Keyboard::Z) {
			gameLayer.setPlayerMoveState(down, true);
		}
	} else if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::A) {
			gameLayer.setPlayerMoveState(left, false);
		} else if (event.key.code == sf::Keyboard::D) {
			gameLayer.setPlayerMoveState(right, false);
		} else if (event.key.code == sf::Keyboard::W) {
			gameLayer.setPlayerMoveState(forward, false);
		} else if (event.key.code == sf::Keyboard::S) {
			gameLayer.setPlayerMoveState(back, false);
		} else if (event.key.code == sf::Keyboard::Q) {
			gameLayer.setPlayerMoveState(up, false);
		} else if (event.key.code == sf::Keyboard::Z) {
			gameLayer.setPlayerMoveState(down, false);
		}
	}

	if (event.type == sf::Event::MouseMoved) {
		dx = (1280 / 2) - event.mouseMove.x;
		dy = (720 / 2) - event.mouseMove.y;
	}
	gameLayer.updatePlayer(0, 0);
}

void GameScene::draw() {
	gameLayer.draw();
}

void GameScene::update(time_t dt) {
	gameLayer.update(dt);
}

