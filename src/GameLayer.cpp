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
	player.update(dt);
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

