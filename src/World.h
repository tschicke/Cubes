/*
 * World.h
 *
 *  Created on: Mar 26, 2013
 *      Author: Tyler
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

#include "Common.h"
#include "ChunkManager.h"

class Player;
namespace ts {

class World {
public:
	World();
	virtual ~World();

	void update(time_t dt);

	void pushCharacter(Player newPlayer);

private:
	ChunkManager chunkManager;
	std::vector<Player> characters;//FIXME change from Player to Character//Should be pointers?

};

} /* namespace ts */
#endif /* WORLD_H_ */
