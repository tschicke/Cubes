/*
 * SpriteSheet.cpp
 *
 *  Created on: May 12, 2013
 *      Author: Tyler
 */

#include "SpriteSheet.h"

#include <iostream>

namespace ts {

SpriteSheet *SpriteSheet::defaultSpriteSheet;

SpriteSheet::SpriteSheet() {
}

void SpriteSheet::initSpriteSheets(){
	defaultSpriteSheet = new SpriteSheet("res/BlockSheet2.DDS");
}

SpriteSheet::SpriteSheet(const char * texturePath){
	init(texturePath);
}

SpriteSheet::~SpriteSheet() {
}

void SpriteSheet::init(const char* texturePath) {
	loaded = loadDDS(texturePath);
}

//Default 16 pixels per element
int SpriteSheet::getElementSizePixels() {
	return 16;
}

} /* namespace ts */
