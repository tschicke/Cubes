/*
 * MainWorld.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Tyler
 */

#ifndef MAINWORLD_H_
#define MAINWORLD_H_

#include "World.h"

namespace ts {

class MainWorld: public ts::World{
public:
	MainWorld();
	virtual ~MainWorld();

	void handleInput();
	void update(time_t dt);
	void draw();

private:
};

} /* namespace ts */
#endif /* MAINWORLD_H_ */
