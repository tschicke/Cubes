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

GameLayer::GameLayer() {
	manager.addChunk(0, 0, 0, 1, 0.5, 0);
	manager.addChunk(Chunk::CHUNK_SIZE, 0, 0, 1, 1, 1);
	manager.addChunk(0, 0, Chunk::CHUNK_SIZE, 0.5, 1, 0);
	manager.addChunk(Chunk::CHUNK_SIZE, 0, Chunk::CHUNK_SIZE, 0, 0.5, 1);
	manager.addChunk(Chunk::CHUNK_SIZE, 0, 2 * Chunk::CHUNK_SIZE, 0, 1, 0);
	manager.addChunk(2 * Chunk::CHUNK_SIZE, 0, 0, 0, 0.5f, 0);
	manager.addChunk(0, 0, 2 * Chunk::CHUNK_SIZE, 1, 0, 1);
	manager.addChunk(2 * Chunk::CHUNK_SIZE, 0, 2 * Chunk::CHUNK_SIZE, 0, 1, 1);
	player.setParent(this);
	player.setPosition(glm::vec3((float) Chunk::CHUNK_SIZE, 30, 5));
}

GameLayer::~GameLayer() {
}

void GameLayer::update(time_t dt) {
	player.update(dt);
}

void GameLayer::handleInput() {
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

	if(ts::Keyboard::checkKeyEvent(ts::Keyboard::Space) == ts::Keyboard::keyPressed){
		player.jump();
	}

	player.setLookStates(ts::Mouse::getLastMove().x, ts::Mouse::getLastMove().y);
//	std::cout << ts::Mouse::getLastMove().x << ", " << ts::Mouse::getLastMove().y << '\n';
}

void GameLayer::draw() {
	manager.draw(player.getMainCamera()->getViewMatrix()); //Temp
}

ChunkManager * GameLayer::getManagerPointer(){
	return &manager;
}
