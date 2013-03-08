/*
 * GameLayer.cpp
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "GameLayer.h"

GameLayer::GameLayer() {
	chunk.init(0, 0, 0);
}

GameLayer::~GameLayer() {
}

void GameLayer::update(time_t dt){
	player.update();
}

void GameLayer::draw(){
	chunk.draw(player.getMainCamera()->getViewMatrix());
}

void GameLayer::updatePlayer(int dx, int dy){
	player.look(dx, dy);
}

void GameLayer::setPlayerMoveState(int state, bool value){
	player.setMovementState(state, value);
}

