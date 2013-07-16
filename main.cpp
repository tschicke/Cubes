/*
 * main.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: Tyler
 */

#include "src/GameWindow.h"
#include "src/MenuScene.h"

int main() {
	GameWindow * window = GameWindow::getMainWindow();
	window->create(1280, 720, "Cubes Textured");
	window->setScene(new MenuScene);
	window->run();

	delete window;

	return 0;
}

