/*
 * GameLayer.h
 *
 *  Created on: Mar 2, 2013
 *      Author: Tyler
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "Layer.h"
#include "Chunk.h"
#include "Player.h"

class GameLayer: public Layer {
public:
	GameLayer();
	virtual ~GameLayer();

	void draw();
	void update(time_t dt);
	void handleInput();

	void updatePlayer(int dx, int dy);//Temp??
	void setPlayerMoveState(MovementState state, bool value);//Temp?
private:
	Chunk chunk;

	Player player;
};

#endif /* GAMELAYER_H_ */
