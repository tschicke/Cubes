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
	player.update(dt);
}

void GameLayer::handleInput() {
	player.input();
	//	std::cout << ts::Mouse::getLastMove().x << ", " << ts::Mouse::getLastMove().y << '\n';
}

void GameLayer::draw() {
	manager.draw(player.getCameraViewMatrix()); //Temp
}

ChunkManager * GameLayer::getManagerPointer(){
	return &manager;
}
