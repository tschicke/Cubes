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
	player = Player(new ts::World);
	manager.addChunk(0, 0, 0, 1, 0, 0);
	manager.addChunk(Chunk::CHUNK_SIZE, 0, 0, 1, 1, 1);
	manager.addChunk(0, 0, Chunk::CHUNK_SIZE, 1, 0, 1);
	manager.addChunk(Chunk::CHUNK_SIZE, 0, Chunk::CHUNK_SIZE, 0, 0, 1);
	manager.addChunk(Chunk::CHUNK_SIZE, 0, 2 * Chunk::CHUNK_SIZE, 0, 1, 0);
	manager.addChunk(2 * Chunk::CHUNK_SIZE, 0, 0, 0, 0.5f, 0);
	manager.addChunk(0, 0, 2 * Chunk::CHUNK_SIZE, 1, 0, 1);
	manager.addChunk(2 * Chunk::CHUNK_SIZE, 0, 2 * Chunk::CHUNK_SIZE, 0, 1, 1);
	player.setPosition(glm::vec3((float) Chunk::CHUNK_SIZE, 30, 5));
}

GameLayer::~GameLayer() {
}

void GameLayer::update(time_t dt) {
	world.update(dt);
}

void GameLayer::handleInput() {
	world.handleInput();
}

void GameLayer::draw() {
}
