/*
 * GameLayer.cpp
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "GameLayer.h"
#include "Keyboard.h"

GameLayer::GameLayer() {
	chunk.init(0, 0, 0);
}

GameLayer::~GameLayer() {
}

void GameLayer::update(time_t dt){
	player.update(dt);
}

void GameLayer::handleInput(){
	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::A) == ts::Keyboard::keyPressed) {
			player.setMovementState(left, true);
		} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::D) == ts::Keyboard::keyPressed) {
			player.setMovementState(right, true);
		} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::W) == ts::Keyboard::keyPressed) {
			player.setMovementState(forward, true);
		} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::S) == ts::Keyboard::keyPressed) {
			player.setMovementState(back, true);
		} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Q) == ts::Keyboard::keyPressed) {
			player.setMovementState(up, true);
		} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Z) == ts::Keyboard::keyPressed) {
			player.setMovementState(down, true);
		}

		if (ts::Keyboard::checkKeyEvent(ts::Keyboard::A) == ts::Keyboard::keyReleased) {
			player.setMovementState(left, false);
		} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::D) == ts::Keyboard::keyReleased) {
			player.setMovementState(right, false);
		} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::W) == ts::Keyboard::keyReleased) {
			player.setMovementState(forward, false);
		} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::S) == ts::Keyboard::keyReleased) {
			player.setMovementState(back, false);
		} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Q) == ts::Keyboard::keyReleased) {
			player.setMovementState(up, false);
		} else if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Z) == ts::Keyboard::keyReleased) {
			player.setMovementState(down, false);
		}
}

void GameLayer::draw(){
	chunk.draw(player.getMainCamera()->getViewMatrix());//Temp
}

void GameLayer::updatePlayer(int dx, int dy){
	player.setLookStates(dx, dy);
}

void GameLayer::setPlayerMoveState(MovementState state, bool value){
	player.setMovementState(state, value);
}

