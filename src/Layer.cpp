/*
 * Layer.cpp
 *
 *  Created on: Jan 30, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "Layer.h"

Layer::Layer() {
	parentScene = NULL;
}

Layer::~Layer() {
}

void Layer::setParentScene(GameScene* parent) {
	parentScene = parent;
}
