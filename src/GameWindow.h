/*
 * GameWindow.h
 *
 *  Created on: Jan 27, 2013
 *      Author: Tyler
 */

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <SFML/Window.hpp>

#include "Scene.h"
#include "Renderer.h"
#include "Common.h"

class GameWindow : public sf::Window{
public:
	GameWindow();
	GameWindow(int w, int h, const char * title);
	virtual ~GameWindow();

	void create(int w, int h, const char * title);
	void run();

	void setScene(Scene * scene);
	Scene * getCurrentScene();//??
private:
	using sf::Window::create;
	int width, height, fpsCounter;
	const char * title;
	bool running;

	void initGL();
	void handleInput();
	void update(time_t dt);
	void render();
	
	void cleanUp();

	Scene * currentScene; //Test
};

#endif /* GAMEWINDOW_H_ */
