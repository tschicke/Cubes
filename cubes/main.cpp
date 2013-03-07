/*
 * main.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: Tyler
 */

#include "src/GameWindow.h"
#include "src/GameScene.h"

int main() {
	GameWindow window;
	window.create(1280, 720, "Cubes Textured");
	window.setScene(new GameScene);
	window.run();

	return 0;
}

