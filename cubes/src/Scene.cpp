/*
 * Scene.cpp
 *
 *  Created on: Jan 30, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "Scene.h"

#include "Layer.h"
#include "Sprite3D.h"

#include <vector>

Scene::Scene() {//Scene class should be pretty empty, subclasses should have actual stuff in them
	Chunk * sprite = new Chunk(0, 0, 0);
	addChild(sprite);
}

Scene::~Scene() {
	for (unsigned int i = 0; i < children.size(); i++) {
		Chunk * child = children.at(i);
		delete child;
		child = NULL;
	}
	children.clear();
}

void Scene::handleInput(sf::Event event) {
}

void Scene::update(time_t dt) {
	for (unsigned int i = 0; i < children.size(); i++) {
			Chunk * child = children.at(i);
			if(child != NULL)child->update(dt);
		}
}

void Scene::addChild(Chunk * chunk) {
	children.push_back(chunk);
}

void Scene::draw(Renderer * renderer) {
	for (unsigned int i = 0; i < children.size(); i++) {
		Chunk * child = children.at(i);
		if(child != NULL)child->draw(renderer);
	}
}

