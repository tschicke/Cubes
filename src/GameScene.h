/*
 * GameScene.h
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "Scene.h"
#include "GameLayer.h"
#include "HudLayer.h"

class GameScene: public Scene {
public:
	GameScene();
	virtual ~GameScene();

	void handleInput();
	void update(time_t dt);
	void draw();

	//Should just use friend classes?
	GameLayer * getGameLayer();
	HudLayer * getHudLayer();
private:
	GameLayer gameLayer;
	HudLayer hud;
};

#endif /* GAMESCENE_H_ */
