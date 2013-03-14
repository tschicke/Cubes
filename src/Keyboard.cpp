/*
 * Keyboard.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: Tyler
 */

#include "Keyboard.h"

namespace ts {

bool Keyboard::keys[];
Keyboard::KeyEvent Keyboard::keyEvents[];

Keyboard::Keyboard() {

}

Keyboard::~Keyboard() {
}

void Keyboard::clearEvents(){
	for (int i = 0; i < keyCount; i++){
		keyEvents[i] = defaultEventType;
	}
}

void Keyboard::setKey(int key, bool value){
	keys[key] = value;
}

bool Keyboard::isKeyPressed(Key key){
	return keys[key];
}

void Keyboard::setKeyEvent(int key, KeyEvent type){
	keyEvents[key] = type;
}

Keyboard::KeyEvent Keyboard::checkKeyEvent(Key key){
	return keyEvents[key];
}

} /* namespace ts */
