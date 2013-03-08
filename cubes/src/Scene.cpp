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
}

Scene::~Scene() {
}

void Scene::handleEvent(sf::Event event) {
}

void Scene::update(time_t dt) {
}

void Scene::draw() {
}

