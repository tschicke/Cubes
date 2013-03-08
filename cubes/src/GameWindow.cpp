/*
 * GameWindow.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: Tyler
 */

#include <iostream>

#include <gl/glew.h>

#include "GameWindow.h"
#include "Texture.h"
#include "FirstPersonCamera.h"

using namespace sf;

GameWindow::GameWindow() {
	currentScene = NULL;
	title = NULL;
	width = 0;
	height = 0;
	fpsCounter = 0;
	running = false;
}

GameWindow::GameWindow(int w, int h, const char * title) {
	create(w, h, title);
}

GameWindow::~GameWindow() {
}

void GameWindow::create(int w, int h, const char * title) {
	width = w;
	height = h;
	this->title = title;
	running = false;
	create(VideoMode(w, h, 32), title);
	setVerticalSyncEnabled(true);
	initGL();
}

void GameWindow::initGL() {
	glClearColor(0.f, 0.0f, 0.4f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW did not initialize properly\n";
	}

	Texture::initTextures();
}

void GameWindow::setScene(Scene * scene) {
	currentScene = scene;
}

Scene * GameWindow::getCurrentScene() {
	return currentScene;
}

void GameWindow::run() {
	running = true;

	long dt;

	Clock clock;
	while (running) {
		dt = clock.restart().asMilliseconds();
		handleInput();
		update(dt);
		render();
		fpsCounter += dt;
		if (fpsCounter >= 1000) {
			std::cout << 1000.f / dt << std::endl;
			fpsCounter = 0;
		}
	}
	cleanUp();
}

void GameWindow::handleInput() {
	Event event;
	while (pollEvent(event)) {
		if (event.type == Event::Closed) {
			running = false;
		} else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
			running = false;
		} else {
			currentScene->handleEvent(event);
		}
	}
}

void GameWindow::update(time_t dt) {
	currentScene->update(dt);
}

void GameWindow::render() { //Watch for too high framerate
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentScene->draw();

	display();
}

void GameWindow::cleanUp() {
}

