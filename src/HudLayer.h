/*
 * HudLayer.h
 *
 *  Created on: Jun 16, 2013
 *      Author: Tyler
 */

#ifndef HUDLAYER_H_
#define HUDLAYER_H_

#include "Layer.h"

class HudLayer: public Layer {
public:
	HudLayer();
	virtual ~HudLayer();

	void draw();
	void update(time_t dt);
	void handleInput();
};

#endif /* HUDLAYER_H_ */
