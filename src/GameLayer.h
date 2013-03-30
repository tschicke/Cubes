/*
 * GameLayer.h
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "Layer.h"
#include "ChunkManager.h"
#include "Player.h"
#include "World.h"

class GameLayer: public Layer {
public:
	GameLayer();
	virtual ~GameLayer();

	void draw();
	void update(time_t dt);
	void handleInput();

	ChunkManager * getManagerPointer();
private:
	ChunkManager manager;

	Player player;
};

#endif /* GAMELAYER_H_ */
