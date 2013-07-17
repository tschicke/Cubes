/*
 * MenuScene.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Tyler
 */

#ifndef MENUSCENE_H_
#define MENUSCENE_H_

#include "Scene.h"

#include "GUIButton.h"

class MenuScene: public Scene {
public:
	MenuScene();
	virtual ~MenuScene();

	void handleInput();
	void update(time_t dt);
	void draw();

private:
	GUIButton playButton;
	GUIButton closeButton;
};

#endif /* MENUSCENE_H_ */
