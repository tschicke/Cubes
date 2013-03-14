/*
 * Keyboard.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: Tyler
 */

#include "Keyboard.h"

namespace ts {

Keyboard::Keyboard() {

}

Keyboard::~Keyboard() {
}

void Keyboard::setKey(Key key, bool value){
	keys[key] = value;
}

} /* namespace ts */
