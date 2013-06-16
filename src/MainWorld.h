/*
 * MainWorld.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Tyler
 */

#ifndef MAINWORLD_H_
#define MAINWORLD_H_

#include "World.h"

#include "Character.h"
#include "Player.h"

#include <glm/glm.hpp>

namespace ts {

class MainWorld: public ts::World{
public:
	MainWorld();
	virtual ~MainWorld();

	void handleInput();
	void update(time_t dt);
	void draw();

private:
	std::vector<Character *> characters;
	Player * mainPlayer;
};

} /* namespace ts */
#endif /* MAINWORLD_H_ */
